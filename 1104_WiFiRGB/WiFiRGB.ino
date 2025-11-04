#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <AsyncTCP.h>


AsyncWebServer ESP32WebServer(80);

String indexHTML = R"rawliteral(<!doctype html>
<html lang="zh-CN">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>ESP32S3控制RGB</title>
  </head>
  <body>
    <div>
    	<input type="checkbox" id="ckbROn" onClick="lightUpRGB()"> <label for="ckbROn">红灯</label> <br>
    	<input type="checkbox" id="ckbGOn" onClick="lightUpRGB()"> <label for="ckbGOn">绿灯</label> <br>
    	<input type="checkbox" id="ckbBOn" onClick="lightUpRGB()"> <label for="ckbBOn">蓝灯</label> <br>
    </div>
  </body>
</html>
<script>
	function lightUpRGB()
	{
		var isROn = document.getElementById("ckbROn").checked ? 0 : 1;
		var isGOn = document.getElementById("ckbGOn").checked ? 0 : 1;
		var isBOn = document.getElementById("ckbBOn").checked ? 0 : 1;
		
		var ajax = new XMLHttpRequest();
		var url = "?r="+isROn+"&g="+isGOn+"&b="+isBOn+"";			//格式为：?r=0&g=1&b=0
		console.log(url);
		ajax.open("GET",url,true);
		ajax.send();
	}
</script>
)rawliteral";

#define rPin 4
#define bPin 5
#define gPin 6

uint8_t leftSeconds = 60;
const char* sid = "rfid";
const char* pwd = "dadadada";

void setup() {
  // put your setup code here, to run once:
  pinMode(rPin, OUTPUT);  digitalWrite(rPin, 1);
  pinMode(bPin, OUTPUT);  digitalWrite(bPin, 1);
  pinMode(gPin, OUTPUT);  digitalWrite(gPin, 1);
  Serial.begin(115200);
  WiFi.disconnect(true);
  WiFi.begin(sid, pwd);

  while(WiFi.status() != WL_CONNECTED && --leftSeconds > 0) {
    delay(1000);
    Serial.println("Connecting ..." + String(leftSeconds));
  }
  
  if(leftSeconds == 0) {
    Serial.println("Time out!");
  } else {
    Serial.println("Succeed connected!");

    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");

    ESP32WebServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      if(request->getParam("r")) {
        digitalWrite(rPin, request->getParam("r")->value().toInt());
      } else {
        digitalWrite(rPin, 1);
      }

      if(request->getParam("g")) {
        digitalWrite(gPin, request->getParam("g")->value().toInt());
      } else {
        digitalWrite(gPin, 1);
      }

      if(request->getParam("b")) {
        digitalWrite(bPin, request->getParam("b")->value().toInt());
      } else {
        digitalWrite(bPin, 1);
      }

      request->send(200,"text/html",indexHTML);
    });

    ESP32WebServer.begin();
        delay(50000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
