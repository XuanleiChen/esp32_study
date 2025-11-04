#include <WiFi.h>
const char* ssid="rfid";
const char* pwd="dadada888";
uint8_t leftSeconds =10;
void setup() 
{
Serial.begin(115200);
WiFi.begin(ssid,pwd);
}

void loop() 
{
while (WiFi.status() != WL_CONNECTED && leftSeconds > 0) {
  delay(1000);
  leftSeconds --;
  Serial.println("Connecting... " + String(10 - leftSeconds));
}

if (leftSeconds == 0) {
  Serial.println("Time out!");
   delay(5000);
} else {
  Serial.println("Succeed connected!");
  Serial.print("IP is: ");
    Serial.println(WiFi.localIP());

  delay(5000);
}
}
