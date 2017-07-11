#ifndef MOTORCALLBACK_H
#define MOTORCALLBACK_H

#include "Arduino.h"
#include "DeviceInfo.h"

class MotorCallback {

public:
    virtual void setTargetDistance(int distance);
	virtual int getTargetDistance();
	virtual void notifyMovedTargetDistance();
	virtual int getDistancePerStep();
	virtual void setDistancePerStep(int distance);
	virtual DeviceInfo getDeviceInfo();
	virtual void setDeviceInfo(DeviceInfo device);
};

#endif