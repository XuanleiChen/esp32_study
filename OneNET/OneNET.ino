#include <WiFi.h>
#include <DHT.h>
#include <PubSubClient.h>
#include <Ticker.h>

DHT myDHT11(11, DHT11);
WiFiClient myWiFiClient;
PubSubClient myPubSubClient(myWiFiClient);
Ticker myTicker;
void uploadData(void);
uint8_t remainSeconds = 60;


//WiFi连接密码
#define WiFi_SID "OneNET"
#define WiFi_PWD "dadadada"

//OneNET连接密码
#define PRODUCT_ID "Fh07EA2zT8"
#define DEVICE_NAME "DHT11OLED"
#define TOKEN_NAME "D6vl/WGHUUGxyU+/5dVrld0FCwFxZcUTW7+tm6+Jj8k="


//MQTT服务器地址
#define MQTT_SERVER_URL "mqtts.heclouds.com"
#define MQTT_SERVER_PORT 1883

//设备属性上报
#define DEVICE_PROP_POST_REQUEST "/sys/%s/%s/things/property/post"
#define DEVICE_PROP_POST_RESPONSE "/sys/%s/%s/things/property/post_reply"
#define DEVICE_PROP_SET_REQUEST "/sys/%s/%s/things/property/set"
#define DEVICE_PROP_SET_RESPONSE "/sys/%s/%s/things/property/set_reply"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.disconnect(true);
  WiFi.begin(WiFi_SID, WiFi_PWD);

  while(WiFi.status() != WL_CONNECTED && --remainSeconds > 0) {
    delay(1000);
    Serial.println("WiFi Connecting ..." + String(remainSeconds));
  }

  if(remainSeconds == 0) {
    Serial.println("Failed Connected to WiFi!");
  } else {
    Serial.println("Succeed Connected to WiFi!");
    remainSeconds = 10;
    /*OneNET连接*/
  myPubSubClient.setServer(MQTT_SERVER_URL, MQTT_SERVER_PORT);
  myPubSubClient.connect(DEVICE_NAME, PRODUCT_ID, TOKEN_NAME);
while (!myPubSubClient.connected() && --remainSeconds > 0) {
  delay(1000);
  Serial.println("OneNET Connecting ..." + String(remainSeconds));
}
if (remainSeconds == 0) {
  Serial.println("Failed connected to OneNET!");
} else {
  Serial.println("Succeed connected to OneNET!");
}
  }
}



void loop() {
  // put your main code here, to run repeatedly:
}