#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
IPAddress apIP(192, 187, 0, 55);
const char* ssid = "MyLeds";         //שם הרשת שיוצג
const char* password = "123456678";  // הסיסמה לרשת אם נרצה להשתמש בה
ESP8266WebServer server(80);

void wifi_setup() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
}

void handleNotFound() {

  String message = "File Not Found \n \n";

  message += "URI: ";

  message += server.uri();

  message += "\nMethod: ";

  message += (server.method() == HTTP_GET) ? "GET" : "POST";

  message += "\nArguments: ";

  message += server.args();

  message += "\n";



  for (uint8_t i = 0; i < server.args(); i++) {

    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }



  server.send(404, "text/plain", message);
}

void handleRoot() {
  char html[5000];
  strcat(html, "<!DOCTYPE html>");
  strcat(html, "<html lang='en'>");
  strcat(html, "<head>");
  strcat(html, "    <meta charset='UTF-8'>");
  strcat(html, "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  strcat(html, "    <title>LED Control (Pure CSS)</title>");
  strcat(html, "    <style>");
  strcat(html, "body {");
  strcat(html, "    display: flex;");
  strcat(html, "    flex-wrap: wrap;");
  strcat(html, "    justify-content: center;");
  strcat(html, "    padding: 20px;");
  strcat(html, "    background-color: #f4f4f9;");
  strcat(html, "}");
  strcat(html, ".ledCard {");
  strcat(html, "    width: 200px;");
  strcat(html, "    height: 180px;");
  strcat(html, "    margin: 20px;");
  strcat(html, "    background-color: #fff;");
  strcat(html, "    border-radius: 12px;");
  strcat(html, "    box-shadow: 0 8px 15px rgba(0, 0, 0, 0.1);");
  strcat(html, "    display: flex;");
  strcat(html, "    flex-direction: column;");
  strcat(html, "    overflow: hidden;");
  strcat(html, "}");
  strcat(html, ".buttons {");
  strcat(html, "    display: flex;");
  strcat(html, "    justify-content: space-around;");
  strcat(html, "    align-items: center;");
  strcat(html, "    padding: 10px 0;");
  strcat(html, "}");
  strcat(html, ".led-state-input {");
  strcat(html, "    display: none;");
  strcat(html, "}");
  strcat(html, ".void {");
  strcat(html, "    width: 100%;");
  strcat(html, "    height: 70%;");
  strcat(html, "    border-top-left-radius: 12px;");
  strcat(html, "    border-top-right-radius: 12px;");
  strcat(html, "    background-color: #333;");
  strcat(html, "    transition: 0.5s all ease;");
  strcat(html, "}");
  strcat(html, "input[type='radio']:checked ~ .void {");
  strcat(html, "    box-shadow: 0 0 20px 5px;");
  strcat(html, "}");
  strcat(html, "#red input[type='radio']:checked ~ .void {");
  strcat(html, "    background-color: #ff4d4d;");
  strcat(html, "    box-shadow: 0 0 25px 5px #ff4d4d, 0 0 45px 10px rgba(255, 77, 77, 0.7);");
  strcat(html, "}");
  strcat(html, "#blue input[type='radio']:checked ~ .void {");
  strcat(html, "    background-color: #4d4dff;");
  strcat(html, "    box-shadow: 0 0 25px 5px #4d4dff, 0 0 45px 10px rgba(77, 77, 255, 0.7);");
  strcat(html, "}");
  strcat(html, "#green input[type='radio']:checked ~ .void {");
  strcat(html, "    background-color: #4dff4d;");
  strcat(html, "    box-shadow: 0 0 25px 5px #4dff4d, 0 0 45px 10px rgba(77, 255, 77, 0.7);");
  strcat(html, "}");
  strcat(html, "#yellow input[type='radio']:checked ~ .void {");
  strcat(html, "    background-color: #ffff4d;");
  strcat(html, "    box-shadow: 0 0 25px 5px #ffff4d, 0 0 45px 10px rgba(255, 255, 77, 0.7);");
  strcat(html, "}");
  strcat(html, ".buttons > .button {");
  strcat(html, "    padding: 8px 16px;");
  strcat(html, "    border-radius: 8px;");
  strcat(html, "    cursor: pointer;");
  strcat(html, "    text-align: center;");
  strcat(html, "    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;");
  strcat(html, "    font-size: 12px;");
  strcat(html, "    font-weight: 600;");
  strcat(html, "    text-transform: uppercase;");
  strcat(html, "    letter-spacing: 0.5px;");
  strcat(html, "    background-color: #007bff;");
  strcat(html, "    color: white;");
  strcat(html, "    transition: background-color 0.3s ease, transform 0.1s ease, box-shadow 0.3s ease;");
  strcat(html, "    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);");
  strcat(html, "}");
  strcat(html, ".buttons > .button:hover {");
  strcat(html, "    background-color: #0056b3;");
  strcat(html, "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);");
  strcat(html, "    transform: translateY(-2px);");
  strcat(html, "}");
  strcat(html, ".buttons > .button:active {");
  strcat(html, "    background-color: #004085;");
  strcat(html, "    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);");
  strcat(html, "    transform: translateY(0);");
  strcat(html, "}");
  strcat(html, "input[type='radio']:checked + input[type='radio'] + .void + .buttons > .button[for$='-on'],");
  strcat(html, "input[type='radio']:checked + .void + .buttons > .button[for$='-off']");
  strcat(html, "{");
  strcat(html, "    background-color: #28a745;  ");
  strcat(html, "    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);");
  strcat(html, "}");
  strcat(html, "    </style>");
  strcat(html, "</head>");
  strcat(html, "<body>");
  strcat(html, "    <div class='ledCard' id='red'>");
  strcat(html, "        <input type='radio' id='red-on' name='red-state' class='led-state-input'>");
  strcat(html, "        <input type='radio' id='red-off' name='red-state' class='led-state-input' checked>");
  strcat(html, "        <div class='void'></div>");
  strcat(html, "        <div class='buttons'>");
  strcat(html, "            <label for='red-on' class='button'>ON</label>");
  strcat(html, "            <label for='red-off' class='button'>OFF</label>");
  strcat(html, "        </div>");
  strcat(html, "    </div>");
  strcat(html, "    <div class='ledCard' id='blue'>");
  strcat(html, "        <input type='radio' id='blue-on' name='blue-state' class='led-state-input'>");
  strcat(html, "        <input type='radio' id='blue-off' name='blue-state' class='led-state-input' checked>");
  strcat(html, "        <div class='void'></div>");
  strcat(html, "        <div class='buttons'>");
  strcat(html, "            <label for='blue-on' class='button'>ON</label>");
  strcat(html, "            <label for='blue-off' class='button'>OFF</label>");
  strcat(html, "        </div>");
  strcat(html, "    </div>");
  strcat(html, "    <div class='ledCard' id='green'>");
  strcat(html, "        <input type='radio' id='green-on' name='green-state' class='led-state-input'>");
  strcat(html, "        <input type='radio' id='green-off' name='green-state' class='led-state-input' checked>");
  strcat(html, "        <div class='void'></div>");
  strcat(html, "        <div class='buttons'>");
  strcat(html, "            <label for='green-on' class='button'>ON</label>");
  strcat(html, "            <label for='green-off' class='button'>OFF</label>");
  strcat(html, "        </div>");
  strcat(html, "    </div>");
  strcat(html, "    <div class='ledCard' id='yellow'>");
  strcat(html, "        <input type='radio' id='yellow-on' name='yellow-state' class='led-state-input'>");
  strcat(html, "        <input type='radio' id='yellow-off' name='yellow-state' class='led-state-input' checked>");
  strcat(html, "        <div class='void'></div>");
  strcat(html, "        <div class='buttons'>");
  strcat(html, "            <label for='yellow-on' class='button'>ON</label>");
  strcat(html, "            <label for='yellow-off' class='button'>OFF</label>");
  strcat(html, "        </div>");
  strcat(html, "    </div>");
  strcat(html, "</body>");
  strcat(html, "</html>");

  server.send(200, "text/html", html);
}

void wifi_loop() {
  server.handleClient();
}