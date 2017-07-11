#include "Motor.h"
#include "UltraSonicWasher.h"
#include "DeviceInfo.h"
#include "Arduino.h"
#include "MotorCallback.h"

UltraSonicWasher::UltraSonicWasher(int* motorPins, int usPin, DeviceInfo d) {
	this->ultrasonicPin = usPin;
	this->motor = new Motor(motorPins, 200, "ultrasonic", this);
	this->curPos = 0;
	this->delaySpeed = 1000;
	this->deviceInfo = &d;
	this->distancePerStep = 2;
	this->watchDistance = 0;
}

void UltraSonicWasher::setRotateDirection(boolean positive) {
  motor->setDirection(positive);
}

void UltraSonicWasher::rotateMotor(int steps) {
  steps = steps < 0 ? steps * (-1) : steps;
  motor->start();
  motor->setDelay(delaySpeed);
  motor->rotate(steps);
}

void UltraSonicWasher::moveWasherTo(int targetRes) {
  int moveRealDistance = (targetRes - curPos) * (*deviceInfo).DEVICE_UV_PHYSICAL_WIDTH;
  Serial.println("UltraSonicWasher: moveWasherTo() targetRes = " + String(targetRes) + ", current pos = " + String(curPos) + ", moveRealDistance = " + String(moveRealDistance));
  setRotateDirection(moveRealDistance > 0 ? true : false);
  int steps = moveRealDistance / distancePerStep;
  rotateMotor(steps);
  
  this->curPos = targetRes;
}

void UltraSonicWasher::turnOnUltraSonic() {
  Serial.println("UltraSonicWasher: UltraSonic ON");
  digitalWrite(this->ultrasonicPin, LOW);
  delay(1000);
}

void UltraSonicWasher::turnOffUltraSonic() {
  Serial.println("UltraSonicWasher: UltraSonic OFF");
  digitalWrite(this->ultrasonicPin, HIGH);
}

void UltraSonicWasher::applyTreatmentToTarget(int targetRes) {
  moveWasherTo(targetRes); 
  turnOnUltraSonic();
}

void UltraSonicWasher::applyTreatmentIfNeeded(boolean* detectedPos) {
  int arrSize = deviceInfo->DEVICE_UV_ARRAY_SIZE;
  for (int i = 0; i < arrSize; i++) {
    if (detectedPos[i]) {
      applyTreatmentToTarget(i);
    }
  }
  turnOffUltraSonic();
  motor->start();
}

void UltraSonicWasher::setTargetDistance(int distance) {
	watchDistance = distance;
}

int UltraSonicWasher::getTargetDistance() {
	return watchDistance;
}

void UltraSonicWasher::notifyMovedTargetDistance() {
    Serial.println("----------------------------------------");
	Serial.println("US: notifyMovedTargetDistance");
}
	
int UltraSonicWasher::getDistancePerStep() {
  return distancePerStep;
}

void UltraSonicWasher::setDistancePerStep(int distance) {
  distancePerStep = distance;
}

DeviceInfo UltraSonicWasher::getDeviceInfo() {
  return *deviceInfo;
}

void UltraSonicWasher::setDeviceInfo(DeviceInfo device) {
  this->deviceInfo = &device;
}