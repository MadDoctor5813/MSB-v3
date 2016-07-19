#include "JoySys.h"

//the amount the speed will be adjusted when the user presses the shoulder buttons
#define LAUNCHER_ADJUST 5

//these are defined to give us a good range, and avoid damaging the motors
#define BANGBANG_MIN 0
#define BANGBANG_MAX 60

//launcher mode, can be naive or bangbang
#define LAUNCHER_NAIVE

enum LrSpeeds {
	FULLCOURT,
	HALFCOURT,
	NONE
};

//utility method for getting the motor speed from the enum
int getMotorSpeedFromEnum(LrSpeeds speed) {
	switch (speed) {
		case FULLCOURT:
			return 60;
		case HALFCOURT:
			return 60;
		case NONE:
			return 0;
	}
	return -1;
}

int getEncoderDeltaFromEnum(LrSpeeds speed) {
	switch (speed) {
		case FULLCOURT:
			return 50;
		case HALFCOURT:
			return 30;
		case NONE: 
			return 0;
	}
}

typedef struct {
	LrSpeeds lrSpeed;

	int userAdjust;

	int leftLast;
	int rightLast;

	int deltaLeft;
	int deltaRight;
} LrState;

LrState lrState;

void lrCalculateDelta() {
	int right = nMotorEncoder[launcherR];
	int left = nMotorEncoder[launcherL];
	lrState.deltaLeft = (left - lrState.leftLast);
	lrState.deltaRight = -(right - lrState.rightLast);
	lrState.rightLast = right;
	lrState.leftLast = left;
	string speedStr;
	stringFormat(speedStr, "L: %d R: %d", lrState.deltaLeft, lrState.deltaRight);
	clearLCDLine(1);
	displayLCDCenteredString(1, speedStr);
}

void lrInit() {
	lrState.lrSpeed = NONE;
}

void lrPollInput() {
	clearLCDLine(1);
	if (joyIsButtonClicked(Btn7U)) {
		lrState.lrSpeed = FULLCOURT;
	}
	if (joyIsButtonClicked(Btn7L)) {
		lrState.lrSpeed = HALFCOURT;
	}
	if (joyIsButtonClicked(Btn7D)) {
		lrState.lrSpeed = NONE;
	}
	//check for manual speed toggle, assign it into a state variable
	if (joyIsButtonClicked(Btn6U)) {
		lrState.userAdjust += LAUNCHER_ADJUST;
	}
	if (joyIsButtonClicked(Btn6D)) {
		lrState.userAdjust -= LAUNCHER_ADJUST;
	}
}

void lrApply() {
//default behavior, same as before
#ifdef LAUNCHER_NAIVE
	//calculate the speed based on the base and whatever the user has input
	int speed = getMotorSpeedFromEnum(lrState.lrSpeed) + lrState.userAdjust;
	//clamp the speed to proper interval
	speed = (speed < 0) ? 0 : speed;
	speed = (speed > 127) ? 127 : speed;
	//assign to motors
	motor[launcherL] = speed;
	motor[launcherR] = speed;
#endif
//only compiles if we've defined LAUNCHER_BANGBANG above
#ifdef LAUNCHER_BANGBANG
	//get the target speed needed from the utility function
	int target = getEncoderDeltaFromEnum(lrState.lrSpeed);
	//if the left motors delta is bigger than the desired target
	if (leftDelta > target) {
		//turn off the motor
		motor[launcherL] = BANGBANG_MIN;
	}
	else {
		//otherwise, its over, turn it to the max 
		motor[launcherL] = BANGBANG_MAX;
	}
	//same with right motor cluster
	if (rightDelta > target) {
		motor[launcherR] = BANGBANG_MIN;
	}
	else {
		motor[launcherR] = BANGBANG_MAX;
	}
#endif
}
