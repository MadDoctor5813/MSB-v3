#include "StructUtil.h"

#define DEAD_ZONE 25

MotorGroup leftDG;
MotorGroup leftUG;
MotorGroup rightDG;
MotorGroup rightUG;

//Utility vector math functions
float vecLength(int x, int y) {
	return (sqrt(pow(x, 2) + pow(y, 2))) - 1;
}

float getVecAngle(int x, int y) {
	// Normalize the given vector
	float length = vecLength(x, y);
	//avoid divide by zero errors
	if (length == 0) {
		return 0;
	}
 	float normX =  x / length;
	float normY =  y / length;
	// Declare a forward vector
	int forwardX = 0;
	int forwardY = 1;
	// Find the relative angle
	float relAngle = atan2(normY, normX) - atan2(forwardY, forwardX);
	// Convert to degrees
	return radiansToDegrees(relAngle);
}

//add proper motors to all groups
void drInit() {
	addMotor(leftUG, leftU);
	addMotor(leftDG, leftD);
	addMotor(rightUG, rightU);
	addMotor(rightDG, rightD);
}

//handle the left joystick
void drPollLeftJoy() {
	int x = -vexRT[Ch4];
	int y = vexRT[Ch3];
	float angle = getVecAngle(x, y);
	int force = vecLength(x, y);
	// Skip to the next iteration if the force is below the dead zone
	if (force < DEAD_ZONE) {
		return;
	}
	// Check forwards, use an OR instead of AND to account the wraparound at the end of the circle
	if (angle > 337.5 || angle < 22.5) {
		addInf(leftDG, force);
		addInf(leftUG, force);
		addInf(rightDG, force);
		addInf(rightUG, force);
	}
	else if (angle > 157.5 && angle < 202.5) {
		addInf(leftDG, -force);
		addInf(leftUG, -force);
		addInf(rightDG, -force);
		addInf(rightUG, -force);
	}

}

void drPollRightJoy() {
	int axis1 = vexRT[Ch1];
	if (abs(axis1) > DEAD_ZONE) {
		if (axis1 > 0) {
			//turn left
			addInf(leftDG, axis1);
			addInf(leftUG, axis1);
			addInf(rightDG, -axis1);
			addInf(rightUG, -axis1);
		}
		else {
			//turn right
			addInf(leftDG, axis1);
			addInf(leftUG, axis1);
			addInf(rightDG, -axis1);
			addInf(rightUG, -axis1);
		}
	}
}

void drPollInput() {
	drPollLeftJoy();
	drPollRightJoy();
}

void drApply() {
	applyGroup(leftDG);
	applyGroup(leftUG);
	applyGroup(rightUG);
	applyGroup(rightDG);
}
