#ifndef POLLUTANTSCANNER_H
#define POLLUTANTSCANNER_H

#include "DeviceInfo.h"
#include "Arduino.h"
#include "DetectorCallback.h"

class PollutantScanner {
private:
	int* sensorPins;
	DeviceInfo* deviceInfo;
	boolean** detectedPos;
	int nextWashPos;
	int nextFoundPos;
	DetectorCallback* obj;
	int detectThreshold;

public:
	PollutantScanner(int* pins, DetectorCallback* cbObj, DeviceInfo d);
	void init();
	void detectUV();
	boolean isPollutantDetected(int sensorPos);
	boolean* getNextWashPosArr();
};
#endif