#ifndef ULTRASONICWASHER_H
#define ULTRASONICWASHER_H

#include "Motor.h"
#include "DeviceInfo.h"
#include "Arduino.h"
#include "MotorCallback.h"

class UltraSonicWasher : public MotorCallback
{
private:
	int watchDistance; 
	int distancePerStep;
	int ultrasonicPin;
	Motor* motor;
	int curPos;
	int delaySpeed;
	DeviceInfo* deviceInfo;

public:
	UltraSonicWasher(int* motorPins, int usPin, DeviceInfo d);
	void setRotateDirection(boolean positive);
	void rotateMotor(int steps);
	void moveWasherTo(int targetResolution);
	void turnOnUltraSonic();
	void turnOffUltraSonic();
	void applyTreatmentToTarget(int targetRes);
	void applyTreatmentIfNeeded(boolean* detectedPos);
	
	// callbacks for motor 
    virtual void setTargetDistance(int distance);
	virtual int getTargetDistance();
	virtual void notifyMovedTargetDistance();
	virtual int getDistancePerStep();
	virtual void setDistancePerStep(int distance);
	virtual DeviceInfo getDeviceInfo();
	virtual void setDeviceInfo(DeviceInfo device);
};

#endif