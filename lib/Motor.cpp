#include "Arduino.h"
#include "Motor.h"
#include "MotorCallback.h"

Motor::Motor(int* pins, int numOfSteps, String name, MotorCallback* cbObj) {
  this->stepPin = pins[0];
  this->dirPin = pins[1];
  this->disablePin = pins[2];
  
  this->shouldStop = true;
  this->stepsPerRevolution = numOfSteps;
  this->stepDelayMicros = 8000;
  this->name = name;
  this->obj = cbObj;
  this->startPos = 0;;
  this->startDistanceCheck = false;
  
  init();
}

void Motor::init() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(disablePin, OUTPUT);
    
  digitalWrite(dirPin, HIGH);                      // 시계방향, Full-Step 모드 설정
  digitalWrite(disablePin, HIGH);
}

void Motor::setDirection(boolean positive) {
  if (positive) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }
}

void Motor::rotateOneStep() {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(stepDelayMicros);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(stepDelayMicros);
  
  //checkTargetDistanceWhileRotating();
}

void Motor::oneRevolution() {
  if (shouldStop) return;
  for (int i = 0; i < stepsPerRevolution; i++) {
    rotateOneStep();
  }
}

void Motor::rotate(int steps) {
  if (shouldStop) return;
  
  int leftoverSteps = steps;
  if (steps > stepsPerRevolution) {
    int numOfRotation = steps / stepsPerRevolution;
	leftoverSteps = steps % stepsPerRevolution;
	for(int i = 0; i < numOfRotation; i++) {
	  oneRevolution();
	}
  }
  
  for (int i = 0; i < leftoverSteps; i++) {
    rotateOneStep();
  }
}
  
void Motor::setDelay(int delay) {
  this->stepDelayMicros = delay;
}

void Motor::stop() {
  if (!shouldStop) {
    digitalWrite(this->disablePin, HIGH);
    this->shouldStop = true;
  }
}

void Motor::start() {
  if (shouldStop) {
    digitalWrite(this->disablePin, LOW);
    this->shouldStop = false;
  }
}

int Motor::getSteps() {
  return this->stepsPerRevolution;
}

String Motor::getName() {
  return this->name;
}

void Motor::checkTargetDistanceWhileRotating() {
  //send callback if motor has moved as much as target distance
  if (startDistanceCheck) {
	  startPos += obj->getDistancePerStep();
	  if (startPos >= obj->getTargetDistance()) {
	  	startDistanceCheck = false;
		startPos = 0;
	    obj->notifyMovedTargetDistance();
	  }
  }
}

void Motor::startTargetDistanceCheck() {
   startDistanceCheck = true;
}

