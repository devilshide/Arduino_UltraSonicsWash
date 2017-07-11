#ifndef DETECTORCALLBACK_H
#define DETECTORCALLBACK_H

#include "Arduino.h"
#include "DeviceInfo.h"

class DetectorCallback {

public:
    virtual void notifyDetected(int distance);
};

#endif