#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RTClib.h>

#include <ESPAsyncWebSrv.h>
#include <WiFi.h>
#include <HTTPClient.h>

//#include <DS3231.h>
//#include <SPI.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);  // set the LCD address to 0x3F for a 16 chars and 2 line display
RTC_DS3231 rtc;

const char* ssid = "Tiago's Galaxy Z Fold5";
const char* password = "ossmurfs";

// Define the number of steps per revolution
const int stepsPerRevolution = 256;
// Create a Stepper object
Stepper myStepper(stepsPerRevolution, 27, 26, 25, 33);

int buzzer = 16;

extern void lcdpilha();
extern void motor();
extern void speaker();

AsyncWebServer server(80);

void setup() {

  Serial.begin(9600);

  comecarLcd();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("IP address: "), Serial.println(WiFi.localIP());
  }
  server.on("/trigger", HTTP_GET, [](AsyncWebServerRequest* request) {
    String variableValue;
    if (request->hasParam("variable")) {
      variableValue = request->getParam("variable")->value();
      Serial.print("Received variable value: ");
      Serial.println(variableValue);

      Serial.println("Rotacao começada");
      motor();
      speaker();
      Serial.println("Rotacao completa");
    }
    request->send(200, "text/plain", "Variavel recebida: " + variableValue);
  });
  server.begin();
}

void loop() {
  updateLcd();
}
