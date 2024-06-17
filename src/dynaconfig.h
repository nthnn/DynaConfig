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

/**
 * @file dynaconfig.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Provides the DynaConfig class for managing
 *        WiFi configuration via a captive portal.
 *
 * This file contains the declaration of the DynaConfig
 * class, which facilitates dynamic WiFi configuration
 * on ESP32 devices using a captive portal. It includes
 * methods for checking WiFi credentials, starting the
 * captive portal, handling HTTP requests, and managing
 * stored credentials.
 * 
 * The captive portal allows users to configure WiFi
 * credentials through a web interface. If credentials
 * are already stored, the device attempts to connect
 * to the specified WiFi network. If no credentials are
 * found, the device starts an access point and serves
 * a configuration page to the user.
 */

#ifndef DYNACONFIG_H
#define DYNACONFIG_H

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <DNSServer.h>
#include <Preferences.h>
#include <WiFi.h>

/**
 * @class DynaConfig
 * @brief Manages dynamic WiFi configuration
 *        through a captive portal.
 *
 * The DynaConfig class sets up an ESP32 device
 * as a WiFi access point with a captive portal.
 * Users can connect to this portal to enter their
 * WiFi credentials, which are then stored in
 * non-volatile memory. The device attempts to
 * connect to the configured WiFi network on
 * subsequent startups.
 */
class DynaConfig {
public:
    /**
     * @brief Construct a new DynaConfig object.
     * 
     * @param captivePortalName The name of the captive portal.
     */
    DynaConfig(const char* captivePortalName);

    /**
     * @brief Checks and manages the WiFi configuration.
     * 
     * If the device has stored WiFi credentials,
     * it stops the DNS server and HTTP server.
     * If no credentials are found, it sets up
     * the device as an access point and starts
     * the captive portal for configuration.
     */
    void checkWiFiConfig();

    /**
     * @brief Closes the Preferences storage.
     */
    void close();

    /**
     * @brief Checks if WiFi credentials are stored in Preferences.
     * 
     * @return true If both SSID and password are stored.
     * @return false If either SSID or password is missing.
     */
    bool hasCredentials();

    /**
     * @brief Removes stored WiFi credentials from Preferences.
     * 
     * @return true If the credentials were successfully removed.
     * @return false If the credentials could not be removed.
     */
    bool removeCredentials();

    /**
     * @brief Retrieves the stored WiFi SSID from Preferences.
     * 
     * @return String The stored SSID.
     */
    String getConfigSSID();

    /**
     * @brief Retrieves the stored WiFi password from Preferences.
     * 
     * @return String The stored password.
     */
    String getConfigPasskey();

private:
    AsyncWebServer server;     ///< The HTTP server instance.
    DNSServer dnsServer;       ///< The DNS server instance.
    Preferences preferences;   ///< The Preferences instance for storing WiFi credentials.
    String portalName;         ///< The name of the captive portal.

    /**
     * @class CaptiveRequestHandler
     * @brief Handles HTTP requests for the captive portal.
     *
     * The CaptiveRequestHandler class is a nested
     * class within DynaConfig that manages incoming
     * HTTP requests. It serves the captive portal
     * page and processes configuration submissions.
     */
    class CaptiveRequestHandler : public AsyncWebHandler {
    public:
        /**
         * @brief Construct a new CaptiveRequestHandler object.
         * 
         * @param html The HTML content to serve as index.
         */
        CaptiveRequestHandler(const char* html);

        /**
         * @brief Determines if the handler can process the request.
         * 
         * @param request The incoming HTTP request.
         * @return true Always returns true to handle all requests.
         */
        bool canHandle(AsyncWebServerRequest *request) override;

        /**
         * @brief Handles the incoming HTTP request.
         * 
         * @param request The incoming HTTP request.
         */
        void handleRequest(AsyncWebServerRequest *request) override;

    private:
        const char* index_html; ///< The HTML content to serve.
    };

    /**
     * @brief Main loop for processing DNS requests.
     * 
     * Continuously processes DNS requests to ensure the captive portal
     * works correctly by redirecting all requests to the portal.
     */
    void handleCycle();

    /**
     * @brief Sets up the HTTP server routes and handlers.
     * 
     * Configures the server to serve the captive portal page and handle WiFi
     * configuration submissions.
     */
    void setupServer();

    static const char* index_html;   ///< The HTML content for the main captive portal page.
    static const char* success_html; ///< The HTML content for the success page.
    static const char* error_html;   ///< The HTML content for the error page.
};

#endif // DYNACONFIG_H