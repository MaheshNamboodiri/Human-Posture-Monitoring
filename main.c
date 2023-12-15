#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
WiFiClient client;
/* defining server port */
ESP8266WebServer server(80);      
#include "ThingSpeak.h"
/* Define WiFi Credentials */-
const char* ssid = "None"; /* Your SSID */
const char* password = "Ashish@6789"; /* Your Password */


const char* serverr = "api.thingspeak.com";
unsigned long myChannelNumber = 1923796;
const char * myWriteAPIKey = "ECOYRKRIOPIFIVS6";
String apiKey = "ECOYRKRIOPIFIVS6";  

int flexs=A0;
int flexdata=0;

void setup()
{
  Serial.begin(9600);
  pinMode(D2, OUTPUT);
  pinMode(flexs,INPUT);
  Wire.begin(D3,D1);
  
  lcd.backlight();
  lcd.print("IOT Project");
  
  
  ThingSpeak.begin(client);
  /* Connectinf to WiFi */
  connectingToWiFi();

  /* Starting Server */
  server.begin();

}
void loop()
{
  lcd.clear();
  flexdata=analogRead(flexs);
  Serial.println(flexdata);
  if (flexdata<90
    
  ){
    digitalWrite(D2, 200);
    lcd.setCursor(0,0);
    lcd.print("Pls be straight");
    }
  else{
    digitalWrite(D2, 0);
   lcd.setCursor(0,0);
   lcd.print("All OK");
    }
  int x = ThingSpeak.writeField(myChannelNumber, 1, flexdata, myWriteAPIKey);
   
  
}
void connectingToWiFi() {
  delay(3000);
  WiFi.disconnect();
  delay(1000);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(1000);
    Serial.print("...");
  }
  Serial.println("Connected");
  Serial.println("Local IP is : ");
  Serial.print((WiFi.localIP().toString()));
  delay(3000);
}
