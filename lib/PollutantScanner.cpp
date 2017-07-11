#include "PollutantScanner.h"
#include "DeviceInfo.h"
#include "Arduino.h"
#include "DetectorCallback.h"

#define DEMO_NO_SENSORS

PollutantScanner::PollutantScanner(int* pins, DetectorCallback* cbObj, DeviceInfo d) {
    this->deviceInfo = &d;
    this->sensorPins = new int[(*deviceInfo).DEVICE_UV_ARRAY_SIZE];
	this->sensorPins[0] = pins[0];
	this->sensorPins[1] = pins[1];
	this->sensorPins[2] = pins[2];
	this->sensorPins[3] = pins[3];
	this->sensorPins[4] = pins[4];
	this->obj = cbObj;
	this->detectedPos = new boolean*[(*deviceInfo).DEVICE_WIDTH_RESOLUTION];

#ifdef DEMO_NO_SENSORS
	boolean detectedPos_demo[12][(*deviceInfo).DEVICE_WIDTH_RESOLUTION] = {
	{true,true,false,true,true},   //0
	{false,true,false,false,true}, //1
	{false,true,false,true,true},  //2
	{true,true,false,false,true},  //3
	{false,true,true,true,true},   //4
	{false,false,true,false,true}, //5
	{true,true,true,true,true},    //6
	{false,true,false,false,true}, //7
	{false,true,false,true,true},  //8
	{true,true,false,false,true},  //9
	{false,true,true,true,true},   //10
	{false,false,true,false,true}};//11

	for(int i = 0; i<12; i++) {
		detectedPos[i] = new boolean[(*deviceInfo).DEVICE_WIDTH_RESOLUTION];
		memcpy(detectedPos[i], detectedPos_demo[i], sizeof(detectedPos_demo[0]));
	}
 #endif
 
	this->nextWashPos = 0;
	this->nextFoundPos = 0;
	this->detectThreshold = (*deviceInfo).DETECTOR_UV_THRESHOLD;
	init();
}

void PollutantScanner::init() {
    int size = sizeof(sensorPins);
	for(int i = 0; i < size; i++) {
	   pinMode(sensorPins[i], INPUT);
	}
}

void PollutantScanner::detectUV() {
#ifdef DEMO_NO_SENSORS
  //Serial.println("PollutantScanner: detectUV() FOR DEMO");
  (*obj).notifyDetected(-1);
#else
  int scanRes = sizeof(sensorPins);
  if (scanRes == 0) return;
  
  boolean pollutantFound = false;
  for (int i = 0; i < scanRes; i++) {
    if (isPollutantDetected(i)) {
	   detectedPos[nextFoundPos][i] = true;
	   pollutantFound = true;
	} else {
	   detectedPos[nextFoundPos][i] = false;
	}
  }
  if (pollutantFound) {
     (*obj).notifyDetected(-1);
     nextFoundPos++;
	 detectedPos[nextFoundPos] = new boolean[(*deviceInfo).DEVICE_WIDTH_RESOLUTION];
  }
 #endif
}

boolean PollutantScanner::isPollutantDetected(int sensorPos) {
	if (digitalRead(sensorPins[sensorPos]) > detectThreshold) {
       return true;
	} else {
	   return false;
	}
}

boolean* PollutantScanner::getNextWashPosArr() {
#ifdef DEMO_NO_SENSORS
	if (nextWashPos == 12) nextWashPos = 0;
#endif
	int nowWashPos = nextWashPos;
	Serial.println("PollutantScanner: getNextWashPosArr() nowWashPos = " + String(nowWashPos));
	nextWashPos++;
	return detectedPos[nowWashPos];
}