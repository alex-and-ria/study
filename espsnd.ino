#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
typedef unsigned short int usi;
#define sda 0
#define scl 2
#define ardaddr 10
#define tnum 5
#define addr1on 11
#define addr1off 10
MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "ntwrk";
const char* password = "1qaz2wsx";

ESP8266WebServer server(80);

String webPage = "";

void setup(void){
  webPage += "<h1>ESP8266 Web Server</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  //pinMode(sndp,OUTPUT);
  Serial.begin(115200);
  Wire.begin(0,2);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    Wire.beginTransmission(ardaddr);
    Wire.write(addr1on);
    Wire.endTransmission();
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    Wire.beginTransmission(ardaddr);
    Wire.write(addr1off);
    Wire.endTransmission();
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
} 
