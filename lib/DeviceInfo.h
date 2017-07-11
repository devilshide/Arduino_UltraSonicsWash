#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include "Arduino.h"

class DeviceInfo {
private:

public:
    const static int DEVICE_UV_ARRAY_SIZE = 5; // TODO: find out
	const static int DEVICE_WIDTH_RESOLUTION = DEVICE_UV_ARRAY_SIZE; 
	const static int DEVICE_PHYSICAL_WIDTH = 540; // TODO: find out
	const static int DEVICE_UV_PHYSICAL_WIDTH = DEVICE_PHYSICAL_WIDTH / DEVICE_UV_ARRAY_SIZE; // This is under the assumption that the sensors are placed uniformly along the axis
	const static int DEVICE_DISTANCE_DETECTOR_WASHER = 420; // TODO: find out
	const static int DEVICE_UV_PHYSICAL_HEIGHT = 50; // height of ultra violet sensor module TODO: find out
	const static int DETECTOR_UV_THRESHOLD = 2;  // TODO: find out
};

#endif