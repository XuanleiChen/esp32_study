#include <ESP32Servo.h>
#include <math.h>
#define SERVO_PIN 4

#define LED_PIN 12   // PWM引脚，UNO上推荐使用9或10

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  for (int i = 0; i < 360; i++) {       // 角度从0到360°
    float rad = i * PI / 180.0;         // 转换为弧度
    float sineValue = sin(rad);         // 计算正弦值（范围 -1 ~ +1）
    int brightness = (sineValue + 1) * 127.5;  // 映射到 0 ~ 255
    analogWrite(LED_PIN, brightness);
    delay(10);  // 调整变化速度
  }
}


