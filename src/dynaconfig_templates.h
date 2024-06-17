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

#ifndef DYNACONFIG_TEMPLATES_H
#define DYNACONFIG_TEMPLATES_H

const char* DynaConfig::index_html = R"rawliteral(
<!DOCTYPE html>
<head>
  <title>DynaWiFiConfig Portal</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <style>
    * {
      font-family:'Courier New', Courier, monospace;
      transition: all 0.3s ease-in-out;
    }

    html, body, h2 {
        margin: 0px;
        padding: 0px;
        background-color: #00db58;
    }

    h2 { background-color: white }

    form {
      height: 100vh;
      width: 100%;
      display: flex;
      justify-content: center;
    }

    table {
      margin-top: 24px;
      padding: 16px;
      border-style: solid;
      border-width: 1px;
      border-color: #1c1d1f;
      background-color: white;
      box-shadow: 10px 10px black;
      position: absolute;
      top: 25%;
    }

    .divider {
        border-style: solid;
        border-color: #1c1d1f;
        border-width: 1px 0px 0px 0px;
        margin: 6px 0px 6px 0px;
        width: 100%;
    }

    label {
      margin-top: 8px;
      padding-right: 12px;
      width: 100%;
    }

    input[type="text"], input[type="password"] {
      border-style: solid;
      border-width: 1px;
      padding: 4px;
      margin-top: 4px;
      width: calc(100% - 10px);
      outline-color: #00db58;
    }

    input[type="submit"] {
      color: white;
      background-color: #00db58;
      border-color: #00db58;
      border-style: solid;
      border-width: 1px;
      padding: 4px 0px 4px 0px;
      margin-top: 8px;
      width: 100%;
    }

    input[type="submit"]:hover, input[type="submit"]:active {
      color: #00db58;
      border-color: #00db58;
      background-color: white;
      font-weight: bold;
    }
  </style>
</head>
<body>
  <form action="/config" method="POST">
    <table>
      <tr>
        <td colspan="2" align="center">
          <h2>DynaWiFiConfig Portal</h2>
          <div class="divider"></div>
        </td>
      </tr>
      <tr>
        <td align="left"><label>SSID:</label></td>
        <td><input type="text" name="ssid" placeholder="WiFi SSID" required /></td>
      </tr>
      <tr>
        <td align="left"><label>Password:</label></td>
        <td><input type="password" name="password" placeholder="WiFi Passkey" required /></td>
      </tr>
      <tr><td colspan="2"><input type="submit" value="Save" /></td></tr>
    </table>
  </form>
</body>
</html>
)rawliteral";

const char* DynaConfig::success_html = R"rawliteral(
<!DOCTYPE html>
<head>
  <title>DynaWiFiConfig Portal</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <style>
    * {
      font-family:'Courier New', Courier, monospace;
    }

    html, body {
        margin: 0px;
        padding: 0px;
        background-color: #00db58;
    }

    .container {
      height: 100vh;
      width: 100%;
      display: flex;
      justify-content: center;
    }

    .box {
      margin-left: 16px;
      margin-right: 16px;
      margin-top: 24px;
      padding: 16px;
      border-style: solid;
      border-width: 1px;
      border-color: #1c1d1f;
      background-color: white;
      box-shadow: 10px 10px black;
      position: absolute;
      top: 30%;
    }
  </style>
</head>
<body>
  <div class="container" align="center">
    <div class="box" align="center">
      <p>Successfully configured WiFi SSID and passkey!</p>
    </div>
  </div>
</body>
</html>
)rawliteral";

const char* DynaConfig::error_html = R"rawliteral(
<!DOCTYPE html>
<head>
  <title>DynaWiFiConfig Portal</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <style>
    * {
      font-family:'Courier New', Courier, monospace;
      transition: all 0.3s ease-in-out;
    }

    html, body {
        margin: 0px;
        padding: 0px;
        background-color: #00db58;
    }

    .container {
      height: 100vh;
      width: 100%;
      display: flex;
      justify-content: center;
    }

    .box {
      margin-left: 16px;
      margin-right: 16px;
      margin-top: 24px;
      padding: 16px;
      border-style: solid;
      border-width: 1px;
      border-color: #1c1d1f;
      background-color: white;
      box-shadow: 10px 10px black;
      position: absolute;
      top: 30%;
    }

    a {
      margin-top: 16px;
      text-decoration: none;
      color: white;
      background-color: #00db58;
      border-color: #00db58;
      border-style: solid;
      border-width: 1px;
      padding: 4px 12px 4px 12px;
      margin-top: 8px;
      width: 100%;
    }

    a:hover, a:active {
      color: #00db58;
      border-color: #00db58;
      background-color: white;
      font-weight: bold;
    }
  </style>
</head>
<body>
  <div class="container" align="center">
    <div class="box" align="center">
      <p>Something went wrong trying to configure WiFi SSID and passkey!</p>
      <a href="/">&#x00AB; Go back</a>
    </div>
  </div>
</body>
</html>
)rawliteral";

#endif