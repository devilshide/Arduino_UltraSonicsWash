#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include "MotorCallback.h"

class Motor {
private:
	int stepPin;
	int dirPin;
	int disablePin;
	int stepsPerRevolution;
	int stepDelayMicros;
	boolean shouldStop;
	String name;
	MotorCallback* obj;
	int startPos;
	boolean startDistanceCheck;
 
public:
	Motor(int* pins, int numOfSteps, String name, MotorCallback* cbObj);
	void init();
	void setDirection(boolean positive);
	void rotateOneStep();
	void oneRevolution();
	void rotate(int steps);
	void setDelay(int delay); 
	void stop();
	void start(); 
	int getSteps();
	String getName();
	void checkTargetDistanceWhileRotating();
	void startTargetDistanceCheck();
};

#endif
