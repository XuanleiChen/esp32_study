
void setup() {
 Serial.begin(115200);
}

void loop() {
  Serial.print("Hello ESP32!  ");
  Serial.println("PI = "+ String(pi,2));
  delay(1000);
}
