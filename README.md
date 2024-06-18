# DynaConfig

![Arduino CI](https://github.com/nthnn/DynaConfig/actions/workflows/arduino_ci.yml/badge.svg) ![Arduino Lint](https://github.com/nthnn/DynaConfig/actions/workflows/arduino_lint.yml/badge.svg)
![Arduino Release](https://img.shields.io/badge/Library%20Manager-v0.0.1-red?logo=Arduino)

DynaConfig is a library for managing WiFi configuration on ESP32 devices using a captive portal. It allows users to dynamically configure WiFi credentials through a web interface, making it easy to set up and change network settings without modifying the firmware.

- **Captive Portal**: Sets up an access point to serve a web page for WiFi configuration.
- **Persistent Storage**: Stores WiFi credentials in non-volatile memory using the Preferences library.
- **Automatic WiFi Connection**: Connects to the stored WiFi network if credentials are available.
- **Fallback Mode**: Starts the captive portal if no credentials are found or if the connection fails.

## Getting Started

### Installation

1. **Clone the Repository**:

    ```sh
    git clone https://github.com/nthnn/DynaConfig.git
    ```

2. **Copy to Arduino Libraries Folder**: Copy the `DynaConfig` folder to your Arduino libraries directory, typically located at `~/Documents/Arduino/libraries` on Linux-based systems.

3. **Include the Library**: In your Arduino sketch, include the library:

    ```cpp
    #include <DynaConfig.h>
    ```

### Usage

Here’s a basic example of how to use the DynaConfig library in your sketch:

```cpp
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
```

## License

Copyright 2024 - Nathanne Isip

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.