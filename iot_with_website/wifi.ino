#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// --- WiFi Configuration ---
IPAddress apIP(55, 55, 55, 55);
const char* ssid = "elyashivLeds";
const char* password = "12345678";
ESP8266WebServer server(80);

void wifi_setup() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.begin(9600);
  Serial.println();
  Serial.print("Access Point Name: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());  // Use WiFi.softAPIP() for reliability
}

void handleNotFound() {
  String message = "File Not Found \n \n";
  message += "URI: " + server.uri() + "\n";
  message += "Method: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: " + String(server.args()) + "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}


// --- 3. The New POST Handler Function ---
// void handlePost() {
//   // Check if any arguments were sent (should be 4, one for each color)
//   if (server.args() > 0) {
//     for (int i = 0; i < server.args(); i++) {
//       String argName = server.argName(i);
//       int state = server.arg(i).toInt();  // "1" for ON, "0" for OFF

//       // Use the helper function defined in LedControl.ino
//       setLedState(argName.c_str(), state);
//     }
//   }

//   // Send a redirect to load the main page again after processing the command
//   server.sendHeader("Location", "/");
//   server.send(302, "text/plain", "OK");
// }



// --- handleRoot (HTML generation) ---
void handleRoot() {
if(server.hasArg("red-state")){
    server.arg("red-state").toInt();
  }
  if(server.hasArg("blue-state")){
    server.arg("blue-state").toInt();
  }
  if(server.hasArg("green-state")){
    server.arg("green-state").toInt();
  }
  if(server.hasArg("yellow-state")){
    server.arg("yellow-state").toInt();
  }
  String html = "";
  String checkedOn;  
  String checkedOff;

  // The vast majority of the HTML is unchanged,
  // but we MUST add the hidden submit button and use Javascript.

  html += "<!DOCTYPE html>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>LED Control (Pure CSS)</title>";
  html += "<style>";
  html += "body {";
  html += "display: flex;";
  html += "flex-wrap: wrap;";
  html += "justify-content: center;";
  html += "padding: 20px;";
  html += "background-color: #f4f4f9;";
  html += "}";
  html += ".ledCard {";
  html += "width: 200px;";
  html += "height: 180px;";
  html += "margin: 20px;";
  html += "background-color: #fff;";
  html += "border-radius: 12px;";
  html += "box-shadow: 0 8px 15px rgba(0, 0, 0, 0.1);";
  html += "display: flex;";
  html += "flex-direction: column;";
  html += "overflow: hidden;";
  html += "}";
  html += ".buttons {";
  html += "display: flex;";
  html += "justify-content: space-around;";
  html += "align-items: center;";
  html += "padding: 10px 0;";
  html += "}";
  html += ".led-state-input {";
  html += "display: none;";
  html += "}";
  html += ".void {";
  html += "width: 100%;";
  html += "height: 70%;";
  html += "border-top-left-radius: 12px;";
  html += "border-top-right-radius: 12px;";
  html += "background-color: #333;";
  html += "transition: 0.5s all ease;";
  html += "}";
  html += "input[type='radio']:checked ~ .void {";
  html += "box-shadow: 0 0 20px 5px;";
  html += "}";
  html += "#red input[type='radio']:checked ~ .void {";
  html += "background-color: #ff4d4d;";
  html += "box-shadow: 0 0 25px 5px #ff4d4d, 0 0 45px 10px rgba(255, 77, 77, 0.7);";
  html += "}";
  html += "#blue input[type='radio']:checked ~ .void {";
  html += "background-color: #4d4dff;";
  html += "box-shadow: 0 0 25px 5px #4d4dff, 0 0 45px 10px rgba(77, 77, 255, 0.7);";
  html += "}";
  html += "#green input[type='radio']:checked ~ .void {";
  html += "background-color: #4dff4d;";
  html += "box-shadow: 0 0 25px 5px #4dff4d, 0 0 45px 10px rgba(77, 255, 77, 0.7);";
  html += "}";
  html += "#yellow input[type='radio']:checked ~ .void {";
  html += "background-color: #ffff4d;";
  html += "box-shadow: 0 0 25px 5px #ffff4d, 0 0 45px 10px rgba(255, 255, 77, 0.7);";
  html += "}";
  html += ".buttons > .button {";
  html += "padding: 8px 16px;";
  html += "border-radius: 8px;";
  html += "cursor: pointer;";
  html += "text-align: center;";
  html += "font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;";
  html += "font-size: 12px;";
  html += "font-weight: 600;";
  html += "text-transform: uppercase;";
  html += "letter-spacing: 0.5px;";
  html += "background-color: #007bff;";
  html += "color: white;";
  html += "transition: background-color 0.3s ease, transform 0.1s ease, box-shadow 0.3s ease;";
  html += "box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);";
  html += "}";
  html += ".buttons > .button:hover {";
  html += "background-color: #0056b3;";
  html += "box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);";
  html += "transform: translateY(-2px);";
  html += "}";
  html += ".buttons > .button:active {";
  html += "background-color: #004085;";
  html += "box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);";
  html += "transform: translateY(0);";
  html += "}";
  html += "input[type='radio']:checked + input[type='radio'] + .void + .buttons > .button[for$='-on'],";
  html += "input[type='radio']:checked + .void + .buttons > .button[for$='-off']";
  html += "{";
  html += "background-color: #28a745; ";
  html += "box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);";
  html += "}";
  html += "</style>";
  html += "<script>";
  html += "function submitDelayed() {";
  html += "  setTimeout(function() {";
  html += "    document.getElementById('led-form').submit();";
  html += "  }, 50);"; // 50 milliseconds delay
  html += "}";
  html += "</script>";
  html += "</head>";
  html += "<body>";

  // The <form> tag is critical for POST requests
html += " <form id='led-form' method='GET'>";

  // ------------------------------------------------------------------
  // RED CARD 🔴
  // ------------------------------------------------------------------
  checkedOn = (redState == HIGH ? " checked" : "");
  checkedOff = (redState == LOW ? " checked" : "");
  
  html += " <div class='ledCard' id='red'>";
  html += "<input type='radio' id='red-on' name='red-state' class='led-state-input' value='1'" + checkedOn + ">";
  html += "<input type='radio' id='red-off' name='red-state' class='led-state-input' value='0'" + checkedOff + ">";
  html += "<div class='void'></div>";
  html += "<div class='buttons'>";
  html += " <label for='red-on' class='button' onclick=\"submitDelayed();\">ON</label>";
  html += " <label for='red-off' class='button' onclick=\"submitDelayed();\">OFF</label>";
  html += "</div>";
  html += " </div>";

  // ------------------------------------------------------------------
  // BLUE CARD 🔵
  // ------------------------------------------------------------------
  checkedOn = (blueState == HIGH ? " checked" : "");
  checkedOff = (blueState == LOW ? " checked" : "");

  html += " <div class='ledCard' id='blue'>";
  html += "<input type='radio' id='blue-on' name='blue-state' class='led-state-input' value='1'" + checkedOn + ">";
  html += "<input type='radio' id='blue-off' name='blue-state' class='led-state-input' value='0'" + checkedOff + ">";
  html += "<div class='void'></div>";
  html += "<div class='buttons'>";
  html += " <label for='blue-on' class='button' onclick=\"submitDelayed();\">ON</label>";
  html += " <label for='blue-off' class='button' onclick=\"submitDelayed();\">OFF</label>";
  html += "</div>";
  html += " </div>";
  
  // ------------------------------------------------------------------
  // GREEN CARD 🟢
  // ------------------------------------------------------------------
  checkedOn = (greenState == HIGH ? " checked" : "");
  checkedOff = (greenState == LOW ? " checked" : "");

  html += " <div class='ledCard' id='green'>";
  html += "<input type='radio' id='green-on' name='green-state' class='led-state-input' value='1'" + checkedOn + ">";
  html += "<input type='radio' id='green-off' name='green-state' class='led-state-input' value='0'" + checkedOff + ">";
  html += "<div class='void'></div>";
  html += "<div class='buttons'>";
  html += " <label for='green-on' class='button' onclick=\"submitDelayed();\">ON</label>";
  html += " <label for='green-off' class='button' onclick=\"submitDelayed();\">OFF</label>";
  html += "</div>";
  html += " </div>";

  // ------------------------------------------------------------------
  // YELLOW CARD 🟡
  // ------------------------------------------------------------------
  checkedOn = (yellowState == HIGH ? " checked" : "");
  checkedOff = (yellowState == LOW ? " checked" : "");

  html += " <div class='ledCard' id='yellow'>";
  html += "<input type='radio' id='yellow-on' name='yellow-state' class='led-state-input' value='1'" + checkedOn + ">";
  html += "<input type='radio' id='yellow-off' name='yellow-state' class='led-state-input' value='0'" + checkedOff + ">";
  html += "<div class='void'></div>";
  html += "<div class='buttons'>";
  html += " <label for='yellow-on' class='button' onclick=\"submitDelayed();\">ON</label>";
  html += " <label for='yellow-off' class='button' onclick=\"submitDelayed();\">OFF</label>";
  html += "</div>";
  html += " </div>";
  html += "</form>";
  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}

void wifi_loop() {
  server.handleClient();
}