#define BEEPPIN  5

void setup() {
  pinMode(BEEPPIN, OUTPUT); 
}

void loop() {
  digitalWrite(BEEPPIN, HIGH);  
  delay(10);  
  digitalWrite(BEEPPIN, LOW); 
  delay(10); 
  digitalWrite(BEEPPIN, HIGH); 
  delay(10); 
  digitalWrite(BEEPPIN, LOW);
  delay(30); 
}
