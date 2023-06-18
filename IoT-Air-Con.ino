/**
 * Internet Connected Air Conditioner API
 */
#include <Arduino.h>
#include "./environment.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

int timer = 0;
ESP8266WebServer server(80);
ESP8266WiFiMulti WiFiMulti;

/**
 * Setup the output pins.
 */
void initPins() {
  for (Button button : buttons) {
    pinMode(button.pin, OUTPUT);
    digitalWrite(button.pin, LOW);
  }
}

/**
 * Setup and connect to a WiFi network.
 */
void initWiFi() {
  // Setup station mode.
  WiFi.mode(WIFI_STA);

  // Stored WiFi credentials.
  for (Network network : network_credentials) WiFiMulti.addAP(network.ssid, network.password);
  delay(2000);

  // Connect to the WiFi.
  connectToWiFi("Connecting");
}

/**
 * Connect to the WiFi.
 */
void connectToWiFi(const String& message) {
  timer = 1;
  Serial.printf("\n[SETUP] %s (%d second)...\n", message.c_str(), timer);
  
  while (WiFiMulti.run() != WL_CONNECTED) {
    timer++;
    Serial.printf("[SETUP] %s (%d seconds)...\n", message.c_str(), timer);
    delay(1000);
    Serial.flush();
  }
  
  onConnected();
}

/**
 * When connection is restored, log the details.
 */
void onConnected() {
  timer = 0;
  Serial.flush();
  Serial.print("[SETUP] Connected to ");
  Serial.print(WiFi.SSID());
  Serial.print(" (");
  Serial.print(WiFi.localIP());
  Serial.println(").");
  
  // Set the hostname,
  WiFi.hostname("AIR-CONDITIONER");
  
  // Configure MDNS.
  if (MDNS.begin("air-conditioner")) {
    Serial.println("[SETUP] MDNS responder started.");
  }

  Serial.println();
}

/**
 * Setup the web server.
 */
void initWebServer() {
  server.onNotFound(handleRequest);
  server.begin();
}

/**
 * Handle a HTTP request.
 */
void handleRequest() {
  String endpoint = server.uri();;
  if (endpoint == "/") return server.send(200, "text/plain", "This is the Air Conditioner API. Please contact Bespoke Technology Labs for more information.");
  if (endpoint.length() > 1) endpoint = endpoint.substring(1);

  for (Button button : buttons) {
    if (button.title == endpoint) return toggleButton(button);
  }

  // If not found, redirect to home.
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

/**
 * Toggle the button when endpoint is hit.
 */
void toggleButton(Button button) {
  digitalWrite(button.pin, HIGH);
  delay(400);
  digitalWrite(button.pin, LOW);
  server.send(200, "text/plain", "The "+button.title+" button on the air conditioner has been toggled.");
}

/**
 * Setup
 */
void setup() {
  Serial.begin(115200);
  initPins();
  initWiFi();
  initWebServer();
}

/**
 * Loop
 */
void loop() {
  if (WiFi.status() != WL_CONNECTED) connectToWiFi("Reconnecting");
  server.handleClient();
}
