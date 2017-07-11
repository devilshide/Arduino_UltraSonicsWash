#ifndef LOADER_H
#define LOADER_H

#include "Motor.h"
#include "DeviceInfo.h"
#include "Arduino.h"
#include "UltraSonicWasher.h"
#include "PollutantScanner.h"

class Loader : public MotorCallback, public DetectorCallback {
private:
	int watchDistance;
	int distancePerStep;
	int distancePerRotation;
	Motor* motor;
	int delaySpeed;
	DeviceInfo* deviceInfo;
	int rotateStart;
	UltraSonicWasher* washer;
	PollutantScanner* scanner;
	int stepsPerSingleScan;

public:
	Loader(int* motorPins, int* scannerPins, int* washerPins, int ultrasonicPin, DeviceInfo d);
	void rotateMotor(int steps);
	void startRotateAndDetect();

	// callbacks from motor
	virtual void setTargetDistance(int distance);
	virtual int getTargetDistance();
	virtual void notifyMovedTargetDistance();
	virtual int getDistancePerStep();
	virtual void setDistancePerStep(int distance);
	virtual DeviceInfo getDeviceInfo();
	virtual void setDeviceInfo(DeviceInfo device);
	
	// callbacks from detector
	virtual void notifyDetected(int distance);
};

#endif