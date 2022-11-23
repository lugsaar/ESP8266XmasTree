// ----------------------------------------
// first try, started by mancas@lug-saar.de
// 2022-11-20
// ----------------------------------------


// LED setup parameters
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
FASTLED_USING_NAMESPACE

#define DATA_PIN            2
#define NUM_LEDS            15
#define MAX_POWER_MILLIAMPS 500
#define LED_TYPE            WS2812B
#define COLOR_ORDER         GRB

#define BRIGHTNESS          48

CRGB leds[NUM_LEDS];


// wifi and webserver setup parameters
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
const char* PARAM_INPUT_1 = "input1";
String globalinputMessage = "empty";  // Website input String
#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "Xmastree";
//const char *password = "12345678";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// HTML web page to handle input
const char index_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML><html><head>
  <title>my XmasTree</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <H3> Welcome to your Xmas tree</H3><br>
  Movie 1 - pacifica<br>
  Movie 2 - pride<br>
  Movie 3 - calme change<br><br>
  <form action="/get">
  chose your LED Movie: <br>
  <input type="text" name="input1"><br>
  <input type="submit" value="Submit">
  </form><br>
  </body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

//void pacifica_loop();



// system setup
void setup() {
 // pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, LOW);

  delay( 3000); // 3 second delay for boot recovery, and a moment of silence
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection( TypicalLEDStrip );
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, MAX_POWER_MILLIAMPS);
  
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  //WiFi.softAP(ssid, password);
  WiFi.softAP(ssid); //open AP
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: "); Serial.println(myIP);

  
  // start the Webserver
  Serial.println("starting webserver");
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
  String inputMessage;
  String inputParam;
   
  // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      globalinputMessage = inputMessage; //gebe weiter an globale Variable
    }
    
  
    else {
      inputMessage = "No message sent";
      inputParam = "none";
      globalinputMessage="empty";
    }
    
    //Serial.println(inputMessage);
    request->send(200, "text/html", "<br><a href=\"/\">You will get it, click to return </a>"); 
    
    }

  );

  server.onNotFound(notFound);
  server.begin();

  }

// run Xmas tree
  
void loop() {
if (globalinputMessage == "1"){
EVERY_N_MILLISECONDS( 20) {
    pacifica_loop();
    FastLED.setBrightness(BRIGHTNESS );
    FastLED.show();
}

}

else if (globalinputMessage == "2") {
    pride();
    FastLED.setBrightness(BRIGHTNESS );
    FastLED.show(); 
} 
}
