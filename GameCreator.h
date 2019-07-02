#pragma once
#include <vector>
// Game Creator
// chooses the buttons that will appear in the challenge

class ButtonConsole;

class GameCreator {
public:
	GameCreator(unsigned int target, unsigned int numButtons,
		ButtonConsole& buttonConsole, bool herrings);

	void GenerateValues();

	unsigned int DecideNumberHerrings();
	int NumberBetween(int min, int max);
	int RandomExistingNumber();
	bool NumberExists(int value, std::vector<int>& vec);

	void CreateRedHerrings(unsigned int);
	int GenerateRandomHerring(); // returns herring value
	void Generate10();

private:
	unsigned int mTarget, mNumButtons;
	ButtonConsole& mButtonConsole;
	bool mIncludeHerrings;

	std::vector<int> mGameVector;
};