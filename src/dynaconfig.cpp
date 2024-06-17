/*
 * This file is part of the Arduino dynaconfig library (https://github.com/nthnn/dynaconfig).
 * Copyright (c) 2024 Nathanne Isip.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "dynaconfig.h"
#include "dynaconfig_templates.h"

DynaConfig::DynaConfig(const char* captivePortalName)
    : portalName(captivePortalName), server(80) { }

void DynaConfig::checkWiFiConfig() {
    this->preferences.begin(this->portalName.c_str());
    if(this->hasCredentials()) {
        this->dnsServer.stop();
        this->server.end();

        return;
    }

    WiFi.mode(WIFI_AP);
    WiFi.softAP(this->portalName);

    this->setupServer();
    this->dnsServer.start(53, "*", WiFi.softAPIP());
    this->handleCycle();
}

void DynaConfig::close() {
    this->preferences.end();
}

bool DynaConfig::hasCredentials() {
    return this->preferences.isKey("ssid") &&
        this->preferences.isKey("password");
}

bool DynaConfig::removeCredentials() {
    return this->preferences.clear();
}

String DynaConfig::getConfigSSID() {
    return this->preferences.getString("ssid", "");
}

String DynaConfig::getConfigPasskey() {
    return this->preferences.getString("password", "");
}

DynaConfig::CaptiveRequestHandler::CaptiveRequestHandler(const char* html)
    : index_html(html) { }

bool DynaConfig::CaptiveRequestHandler::canHandle(AsyncWebServerRequest *request) {
    return true;
}

void DynaConfig::CaptiveRequestHandler::handleRequest(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", this->index_html);
}

void DynaConfig::handleCycle() {
    while(true) {
        this->dnsServer.processNextRequest();
        yield();
    }
}

void DynaConfig::setupServer() {
    this->server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", index_html);
    });

    this->server.on("/config", HTTP_POST, [this](AsyncWebServerRequest *request) {
        if(request->getParam("ssid", true) && request->getParam("password", true)) {
            String ssidParam = request->getParam("ssid", true)->value();
            String passwordParam = request->getParam("password", true)->value();

            if(!ssidParam.isEmpty() && !passwordParam.isEmpty()) {
                this->preferences.putString("ssid", ssidParam);
                this->preferences.putString("password", passwordParam);
                this->preferences.end();

                request->send(200, "text/html", this->success_html);

                this->close();
                delay(500);
                ESP.restart();
                return;
            }
        }

        request->send(200, "text/html", this->error_html);
    });

    server.addHandler(new CaptiveRequestHandler(index_html)).setFilter(ON_AP_FILTER);
    server.begin();
}