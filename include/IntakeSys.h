#define INTAKE_SPEED 127

#include "JoySys.h"

//intake system state struct
typedef struct {
	bool runIntake;
	bool runRoller;
} InState;

InState inState;

void inPollInput() {
	if (joyIsButtonClicked(Btn8D)) {
		inState.runIntake = !inState.runIntake;
	}
	if (joyIsButtonClicked(Btn8U)) {
		inState.runRoller = !inState.runRoller;
	}
}

void inApply() {
	if (inState.runIntake) {
		motor[intake] = 127;
		motor[roller] = 127;
	}
	else {
		motor[intake] = 0;
		motor[roller] = 0;
	}
}
