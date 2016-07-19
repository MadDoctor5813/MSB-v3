#define MAX_BUTTONS 12

typedef struct {
	int last;
	int curr;
	TVexJoysticks buttonId;
} Button;

typedef struct {
	Button buttons[12];
	int numButtons;
} JoyState;

JoyState joyState;

void addButton(TVexJoysticks buttonId) {
	if (joyState.numButtons < MAX_BUTTONS) {
		joyState.buttons[joyState.numButtons].buttonId = buttonId;
		joyState.numButtons++;
	}
	else {
		//maybe display an error
	}
}

Button* getButton(TVexJoysticks buttonId) {
	for (int i = 0; i < joyState.numButtons; i++) {
		if (joyState.buttons[i].buttonId == buttonId) {
			return &joyState.buttons[i];
		}
	}
	return NULL;
}

void joyInit() {
	addButton(Btn7U);
	addButton(Btn7D);
	addButton(Btn7L);
	addButton(Btn7R);
	addButton(Btn8U);
	addButton(Btn8D);
	addButton(Btn8L);
	addButton(Btn8R);
	addButton(Btn5U);
	addButton(Btn5D);
	addButton(Btn6U);
	addButton(Btn6D);
}

void joyPollInput() {
	for (int i = 0; i < joyState.numButtons; i++) {
		Button* current = &joyState.buttons[i];
		current->last = current->curr;
		current->curr = vexRT[current->buttonId];
	}
}

bool joyIsButtonClicked(TVexJoysticks buttonId) {
	Button* button = getButton(buttonId);
	return (button->curr != button->last && button->curr == false);
}
