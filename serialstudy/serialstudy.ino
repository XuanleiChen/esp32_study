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
MyOLED.drawString(0,0,"Hello World");
MyOLED.drawString(0,16,"Hello Arduino");
MyOLED.drawString(0,32,"Hello Chen Xuanlei");
MyOLED.drawString(0,48,"你好");
MyOLED.display();
}
