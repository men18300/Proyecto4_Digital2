/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server
  Basándose en los ejemplos de:
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://electropeak.com/learn
**************************************************************************************************/
//Universidad del Valle de Guatemala
//Depto. de Ingenieria Mecatronica y Electronica
//Curso de Digital 2
//Seccion 20
//Prof. Pablo Mazariegos
//Prof. Kurt Kellner
//Diego Mencos
//Carne 18300


//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

//************************************************************************************************
// Variables globales
//************************************************************************************************
// SSID & Password
const char* ssid = "TURBONETT_523";  // Enter your SSID here
const char* password = "a4c564b0c0";  //Enter your Password here


#define RXD2 16
#define TXD2 17

WebServer server(80);  // Object of WebServer(HTTP port, 80 is default)

int dato = 0;
bool parqueo1 = LOW;
bool parqueo2 = LOW;
bool parqueo3 = LOW;
bool parqueo4 = LOW;

uint8_t LED1pin = 2;
bool LED1status = LOW;
int contador = 0;

//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);


  while (!Serial);
  while (!Serial2);

  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  pinMode(LED1pin, OUTPUT);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // Directamente desde e.g. 192.168.0.8
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);

  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

//************************************************************************************************
// loop principal
//************************************************************************************************
void loop() {

  //Serial.println(contador);
  server.handleClient();

  if (Serial2.available() > 0) {
    dato = Serial2.read();
    // Serial.println(Serial2.read());
    Serial.println(dato);
  }

  if (dato == 97) {
    parqueo1 = HIGH;
  }
  else if (dato == 98) {
    parqueo1 = LOW;
  }
  if (dato == 99) {
    parqueo2 = HIGH;
  }
  else if (dato == 100) {
    parqueo2 = LOW;
  }
  if (dato == 101) {
    parqueo3 = HIGH;
  }
  else if (dato == 102) {
    parqueo3 = LOW;
  }



  if (LED1status)
  {
    digitalWrite(LED1pin, HIGH);
  }
  else
  {
    digitalWrite(LED1pin, LOW);
  }
}

//************************************************************************************************
// Handler de Inicio página
//************************************************************************************************
void handle_OnConnect() {
  LED1status = LOW;
  Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status));
}

//************************************************************************************************
// Handler de led1on
//************************************************************************************************
void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO2 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status));
}

//************************************************************************************************
// Handler de led1off
//************************************************************************************************
void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status));
}

//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML(uint8_t led1stat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Proyecto 4</title>\n";
  ptr += "<body bgcolor=#101010>";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body {margin-top: 50px;} h1 {color: #FFFFFF;margin: 50px auto 30px;}  h4 {color: #FFFFFF;margin: 15px;} h3 {color: #FFFFFF;margin-bottom: 15px;}\n";
  ptr += "table {";
  ptr += "  font-family: Helvetica, sans-serif;";
  ptr += "  border-collapse: collapse;";
  ptr += "  width: 100%;";
  ptr += "  margin: 50px auto 30px;";
  ptr += "  text-align: center;";
  ptr += "}";
  ptr += "td, th {";
  ptr += " border: 1px solid #101010;";
  ptr += " text-align: center;";
  ptr += " padding: 8px;  ";
  ptr += "  background-color: #008080;";
  ptr += "}";
  ptr += "tr:nth-child(even) {";
  ptr += "  background-color: #FFFFFF;";
  ptr += "}  ";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ParqueoMatic-Prototipo &#128664</h1>\n";
  ptr += "<h3>Diego Mencos - 18300 </h3>\n";
  ptr += "<h4>Proyecto 4 </h1>\n";
  ptr += "<h2> </h2>";
  ptr += "<table>";
  ptr += " <table style= margin: 0 auto;>";
  ptr += " <tr>";
  ptr += "   <th><span style='font-size:30px;'>Parqueo 1</th>";
  ptr += "   <th><span style='font-size:30px;'>Parqueo 2 </th>";
  ptr += "   <th><span style='font-size:30px;'>Parqueo 3 </th>";
  ptr += "   <th><span style='font-size:30px;'>Parqueo 4</th>";
  ptr += " </tr>";
  ptr += "  <tr>";

  //ptr +=  "<td> <span style='font-size:60px;'> &#9989;</span></td>";
  //ptr += "<td> <span style='font-size:60px;'>&#10060;</span></td>";
  //ptr += "<td> <span style='font-size:60px;'> &#9989;</span></td>";
  //ptr +=" <td> <span style='font-size:60px;'>&#10060;</span></td>";

  if (parqueo1 == HIGH) {
    ptr +=  "<td> <span style='font-size:60px;'> &#9989;</span></td>";
  }
  else if (parqueo1 == LOW) {
    ptr += "<td> <span style='font-size:60px;'>&#10060;</span></td>";
  }

  if (parqueo2 == HIGH) {
   ptr += "<td> <span style='font-size:60px;'> &#9989;</span></td>";
  }
  else if (parqueo2 == LOW) {
    ptr += "<td> <span style='font-size:60px;'>&#10060;</span></td>";
  }

  if (parqueo3 == HIGH) {
    ptr +=  "<td> <span style='font-size:60px;'> &#9989;</span></td>";
  }
  else if (parqueo3 == LOW) {
    ptr += "<td> <span style='font-size:60px;'>&#10060;</span></td>";
  }

  if (parqueo4 == HIGH) {
    ptr += "<td> <span style='font-size:60px;'> &#9989;</span></td>";
  }
  else if (parqueo4 == LOW) {
    ptr += "<td> <span style='font-size:60px;'>&#10060;</span></td>";
  }



  ptr += " </tr>";
  ptr += "</table>";



  if (led1stat)
  {

    ptr += "<p>Presione el boton para refrescar la pagina.</p><a class=\"button button-off\" href=\"/led1off\">ACT</a>\n";
  }
  else
  {
    ptr += "<p>Presione el boton para refrescar la pagina.</p><a class=\"button button-on\" href=\"/led1on\">ACT</a>\n";
  }

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
