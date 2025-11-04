#include <SSD1306.h>
#include "DHT.h"
#define SCLPin 21
#define SDAPin 47
SSD1306 MyOLED(0x3C,SDAPin,SCLPin);
DHT dht11(11,DHT11);

void setup() {
MyOLED.init();
MyOLED.flipScreenVertically();
MyOLED.setFont(ArialMT_Plain_16);
MyOLED.setTextAlignment(TEXT_ALIGN_LEFT);
MyOLED.clear();
dht11.begin();
}

void loop() {
float t = dht11.readTemperature();
float h = dht11.readHumidity();
MyOLED.drawString(0,0,"TEMP:");
MyOLED.drawString(0,16,String(t,1)+"C");
MyOLED.drawString(0,32,"HUMI:");
MyOLED.drawString(0,48,String(h,1)+"%");
MyOLED.display();
}
