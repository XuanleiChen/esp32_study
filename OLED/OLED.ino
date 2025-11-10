#include <SSD1306.h>

#define SCLPin 21
#define SDAPin 47
SSD1306 MyOLED(0x3C,SDAPin,SCLPin);


void setup() {
MyOLED.init();
MyOLED.flipScreenVertically();
MyOLED.setFont(ArialMT_Plain_16);
MyOLED.setTextAlignment(TEXT_ALIGN_LEFT);
MyOLED.clear();

}

void loop() {
static uint8_t i=1;
MyOLED.clear();
MyOLED.drawString(0,0,"i="+String(i++));
delay(1000);
MyOLED.display();
}
