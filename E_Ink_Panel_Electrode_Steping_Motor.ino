#include <DeviceInfo.h>
#include <Loader.h>
#include <Motor.h>
#include <MotorCallback.h>
#include <UltraSonicWasher.h>



Motor motor(9, 8, 10, 11, 200, "testmotor", NULL);
DeviceInfo d;
void setup() {
//  motor.init();
  
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  motor.setDelay(4000);
  motor.rotate(200);
//  motor.oneRevolution();
 Serial.println("loop(): deviceinfo->A = " + String(d.DEVICE_UV_ARRAY_SIZE));
 Serial.println("loop(): deviceinfo->A = " + String(d.DEVICE_UV_PHYSICAL_WIDTH));
//    digitalWrite(7, HIGH);
//    delay(1000);
//    digitalWrite(7, LOW);
//    delay(1000);
}



//#define stepPin 9
//#define dirPin 8
//#define ms1Pin 11
//#define ms2Pin 10
//
//int stepPerRevolution = 200; //step수 바꿔서 속도조절해보기
//int stepDelayMicros = 5800; //step 사이 delay : min 1000
//
//void setup() {
//  pinMode(stepPin, OUTPUT);
//  pinMode(dirPin, OUTPUT);
//  pinMode(ms1Pin, OUTPUT);
//  pinMode(ms2Pin, OUTPUT);
//}
//
//void loop() {
//  digitalWrite(dirPin, HIGH);                      // 시계방향, Full-Step 모드 설정
//  digitalWrite(ms1Pin, LOW);
//  digitalWrite(ms2Pin, LOW);
//  
//  for (int i = 0; i < stepPerRevolution; i++) {
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(stepDelayMicros);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(stepDelayMicros);
//  }
//}



