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

#include <dynaconfig.h>
#include <WiFi.h>

void setup() {
    // Initialize serial communication at a baud rate of 115200
    Serial.begin(115200);

    // Create an instance of the DynaConfig class with the name "dyna-config" for the captive portal
    DynaConfig dynaConfig("dyna-config");
    // Check WiFi configuration; starts the captive portal if no credentials are found
    dynaConfig.checkWiFiConfig();

    // Set the WiFi mode to station (client)
    WiFi.mode(WIFI_STA);
    // Attempt to connect to the WiFi network using the stored SSID and password
    WiFi.begin(
        dynaConfig.getConfigSSID(),      // Retrieve the stored SSID
        dynaConfig.getConfigPasskey()    // Retrieve the stored password
    );

    // Close the DynaConfig class object
    dynaConfig.close();

    // Indicate that the device is attempting to connect to the WiFi network
    Serial.println("Connecting");
    // Wait until the device is connected to the WiFi network
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");    // Print a dot for each connection attempt
        delay(100);           // Wait for 100 milliseconds before retrying
    }

    // Once connected, print a success message to the serial monitor
    Serial.println("\nConnected to the WiFi network");

    // Print the local IP address assigned to the ESP32
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // Add a small delay to prevent excessive CPU usage in the loop
    delay(10);
}