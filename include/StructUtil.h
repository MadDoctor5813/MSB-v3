#define MAX_MOTORS 4
#define MAX_INFS 10

typedef struct {
	tMotor motors[MAX_MOTORS];
	int numMotors;
	int infs[MAX_INFS];
	int numInfs;
	TSemaphore lock;
} MotorGroup;

void addInf(MotorGroup &group, int influence) {
	if (group.numInfs < MAX_INFS) {
		group.infs[group.numInfs] = influence;
		group.numInfs++;
	}
}

void addMotor(MotorGroup &group, tMotor newMotor) {
	group.motors[group.numMotors] = newMotor;
	group.numMotors++;
}

void applyGroup(MotorGroup& group) {
	//check against divide by zero errors
	if (group.numInfs == 0) {
		for (int i = 0; i < group.numMotors; i++) {
			motor[group.motors[i]] = 0;
		}
		return;
	}
	int infSum = 0;
	for (int i = 0; i < group.numInfs; i++) {
		infSum += group.infs[i];
	}
	int finalMotor = infSum / group.numInfs;
	for (int i = 0; i < group.numMotors; i++) {
			motor[group.motors[i]] = finalMotor;
	}
	//zero out the array
	for (int i = 0; i < group.numInfs; i++) {
		group.infs[i] = 0;
	}
	//reset the count
	group.numInfs = 0;
}
