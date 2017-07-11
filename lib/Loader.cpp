#include "Motor.h"
#include "Loader.h"
#include "DeviceInfo.h"
#include "Arduino.h"
#include "UltraSonicWasher.h"
#include "PollutantScanner.h"

Loader::Loader(int* motorPins, int* scannerPins, int* washerPins, int ultrasonicPin, DeviceInfo d) {
	this->motor = new Motor(motorPins, 200, "loader", this);
	this->delaySpeed = 3000;
	this->deviceInfo = &d;
	this->rotateStart = 0;
	this->distancePerStep = 10;
	this->watchDistance = deviceInfo->DEVICE_DISTANCE_DETECTOR_WASHER;
	this->washer = new UltraSonicWasher(washerPins, ultrasonicPin, d);
	this->scanner = new PollutantScanner(scannerPins, this, d);
	this->stepsPerSingleScan = deviceInfo->DEVICE_UV_PHYSICAL_HEIGHT / distancePerStep;
}

void Loader::rotateMotor(int steps) {
  motor->start();
  motor->setDelay(delaySpeed);
  motor->rotate(steps);
}

void Loader::startRotateAndDetect() {
   rotateMotor(stepsPerSingleScan);
   scanner->detectUV();
   //Serial.println("UltraSonicWasher: startRotateAndDetect, detect END");
}

void Loader::setTargetDistance(int distance) {
	watchDistance = distance;
}

int Loader::getTargetDistance() {
	return watchDistance;
}

void Loader::notifyMovedTargetDistance() {
	// 1. stop belt motor
	//Serial.println("Loader: notifyMovedTargetDistance() > stop motor");
	motor->stop();
	// 2. perform ultrasonic wash
	//Serial.println("Loader: notifyMovedTargetDistance() > apply ultra sonic");
	washer->applyTreatmentIfNeeded((*scanner).getNextWashPosArr());
	// 3. restart belt motor
	//Serial.println("Loader: notifyMovedTargetDistance() > restart motor");
	motor->start();
	//rotateMotor(stepsPerSingleScan);
}
	
int Loader::getDistancePerStep() {
  return distancePerStep;
}

void Loader::setDistancePerStep(int distance) {
  distancePerStep = distance;
}

DeviceInfo Loader::getDeviceInfo() {
  return *deviceInfo;
}

void Loader::setDeviceInfo(DeviceInfo device) {
  this->deviceInfo = &device;
}

void Loader::notifyDetected(int distance) {
  //Serial.println("Loader: notifyDetected() > startTargetDistanceCheck");
  motor->startTargetDistanceCheck();
}