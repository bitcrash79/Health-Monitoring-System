#define BLYNK_TEMPLATE_ID "TMPL3CTgvun28"
#define BLYNK_TEMPLATE_NAME "Health Monitoring system"
#define BLYNK_AUTH_TOKEN "wcN2xktkpwe1d0MxXohHf6dzrEcNHDSL"
#include <DHTesp.h>
#include<Wire.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>

const int sensorPin = 15;
const int pulsePin = 34;
const int led = 2;
BlynkTimer timer;

DHTesp dht;
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup(){
  Serial.begin(115200);
  dht.setup(sensorPin, DHTesp::DHT22);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendDHTData);
  lcd.init();
  lcd.backlight();

}

void sendDHTData() {
  float t = dht.getTemperature();
  Serial.println("Temp is ");
  Serial.println(t);
  float valPulse = analogRead(pulsePin);
  valPulse = map(valPulse, 0, 4095, 60, 100);
  
  if(isnan(t)){
    Serial.println("failed to read from temp sensor.");
    lcd.setCursor(0,0);
    lcd.print("sensor Error!");
    lcd.clear();
    return;

  }
  if(isnan(valPulse)){
    Serial.println("failed to read from temp sensor.");
    lcd.setCursor(0,0);
    lcd.print("sensor Error!");
    lcd.clear();
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("temp: ");
  lcd.print(t);
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("Heart rate: ");
  lcd.print(valPulse);
  lcd.print(" BPM");

  

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, valPulse);


 
}

void loop(){
  Blynk.run();
  timer.run();
}