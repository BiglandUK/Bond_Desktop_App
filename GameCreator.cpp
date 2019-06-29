#include "GameCreator.h"
#include "Button.h"
#include "Utility.h"

GameCreator::GameCreator(unsigned int target, unsigned int numButtons,
	ButtonConsole& buttonConsole, bool herrings)
	: mTarget(target), mNumButtons(numButtons), mButtonConsole(buttonConsole), mIncludeHerrings(herrings)
{}

void GameCreator::GenerateValues() {
	if (mTarget == 10) {
		Generate10();
		return;
	}

	if (mNumButtons > mTarget - 1) mNumButtons = mTarget - 1; // ensure numButtons is valid.
	// This pseudo code has a problem, as the num buttons is set in the caller.
	// Either numButtons should be passed by reference, or a different variable should be used, and blanks
	// created to make up the difference.
	// Ideally, the GameSelector will avoid this situation. So maybe it should be an assert instead.

	unsigned int numHerrings = 0;
	if(mIncludeHerrings)
		numHerrings = DecideNumberHerrings();
	int value = 1; // this is the value for the button to show correct pairs.
	// for each button:
	for (int i = 0; i < mNumButtons - numHerrings; ++i) {
		bool repeat = false;
		int number = -1;
		do { //get a unique number
			number = NumberBetween(1, mTarget);
			repeat = NumberExists(number, mGameVector);
		} while (repeat == true);
		//store this, and the complement, in the gameVector for future uniqueness checks
		mGameVector.emplace_back(number);
		mGameVector.emplace_back(mTarget - number);
		// create two buttons and setup their values
		mButtonConsole.AddButton(value, std::to_string(number));
		mButtonConsole.AddButton(-value, std::to_string(number));
		value++;
	}
	if (numHerrings > 0)
		CreateRedHerrings(numHerrings);
}

unsigned int GameCreator::DecideNumberHerrings() {
	// decide how many red herrings (or blanks - can be decided later, to make the game easier)
	// 9 - 1 herring
	// 12, 16  buttons - 0 or 2 herrings
	// 20 - 0, 2 or 4 herrings
	// 25 - 1, 3 or 5 herrings
	return 1;
}

int GameCreator::NumberBetween(int min, int max) {
	return Random(min, max);
}

int GameCreator::RandomExistingNumber() {
	return mGameVector[Random(0, mGameVector.size() - 1)];
}

bool GameCreator::NumberExists(int value, std::vector<int>& vec) {
	for (auto i : vec) {
		if (value == i) return true;
	}
	return false;
}

void GameCreator::CreateRedHerrings(unsigned int numHerrings) {
	if (mTarget < 100) { // simply find a unique value
		for (int i = 0; i < numHerrings; ++i) {
			// Get a unique number
			bool repeat = false; int number = -1;
			do { //get a unique number
				number = NumberBetween(1, mTarget);
				repeat = NumberExists(number, mGameVector);
			} while (repeat == true);
			// Add it to the checking vector
			mGameVector.emplace_back(number);
			mButtonConsole.AddButton(0, std::to_string(number));
		}
	}
	else { // try something a little cleverer for larger values.
		int number = RandomExistingNumber();
		int plusminus10 = 10 * ((NumberBetween(0, 1) * 2) - 1);
		if (NumberExists(number + plusminus10, mGameVector)) {
			// try the opposite
			if (NumberExists(number - plusminus10, mGameVector)) {
				//now what??

			}

		}

	}
}

// Special case: only 9 numbers to choose, and only 10 possibilities.
void GameCreator::Generate10() {
	// Choose the red herring first and store it
	int herring = NumberBetween(1, 9);
	// not needed? //redherringVec.emplace_back(herring);
	mButtonConsole.AddButton(0, std::to_string(herring));

	// Add all the other possible numbers to the gameVector
	// Cycles through 1-5, skipping over the herring or the partner of the herring.
	for (int i = 1; i < 6; ++i) {
		if (i == herring || herring + i == 10) continue;
		mGameVector.emplace_back(i);
		mGameVector.emplace_back(10 - i);
		mButtonConsole.AddButton(i, std::to_string(i));
		mButtonConsole.AddButton(-i, std::to_string(i));
	}
}