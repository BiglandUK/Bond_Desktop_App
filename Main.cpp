// Bond's Disarming Challenge
// (working title)
// Disarm the bomb by pressing the correct buttons.

#include "Button.h"
#include "GameCreator.h"

int main() {
	srand(time(0));
	ButtonConsole bc;
	unsigned int target = 100;
	unsigned int numButtons = 25;

	GameCreator gc(target, numButtons, bc, true);
	gc.GenerateValues();

	//Display buttons
	bc.DisplayButtons();

	return 0;
}

