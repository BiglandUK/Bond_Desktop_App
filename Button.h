// Button.h
// Coupled to SFML
// This version attempts to separate the button itself from the text and/or image displayed on it.

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Utility.h"
#include "BigSoftEd.h"

class Renderer;

enum class ButtonState{ Normal, Selected, Disabled };


class Button{
public:

protected:
	int value_; // the value of the button for game purposes. 0 means this is a red herring/not involved in the solution.
	//sf::Vector2f position_;    // position on screen - have this controlled elsewhere?
    int width_, height_; // size of graphic and on screen
    ButtonState  state_; // current state
    sf::Vector2i iconPos_, textPos_; // local coordinates on the Button of any icon and/or text
	sf::Sprite icon_; // icon for the button, if any
	std::string text_; // text on the button, if any


public:
	// Constructors
	Button(); // makes a simple, empty button.
	Button( int value, int width, int height );

	void SetState( const ButtonState& state = ButtonState::Normal );
	ButtonState GetState() const;
	void Reset(); // set to normal
	void Select(); // set to selected
	void Disable(); // set to disabled

	void SetDimensions( const int width, const int height );
	int GetWidth() const;
	int GetHeight() const;
    
	void SetIcon(const sf::Sprite& icon);
	const sf::Sprite& GetIcon() const;
    void SetIconPosition(int x, int y);
	const sf::Vector2i& GetIconPosition() const;
	
	void SetText(const std::string& text);
	const std::string& GetText() const;
	void SetTextPosition(int x, int y);
	const sf::Vector2i& GetTextPosition() const;

	void SetValue(int value);
	int Value() const;
};


typedef std::vector<Button> ButtonList;

class ButtonConsole{
public:
	ButtonConsole(Renderer& renderer, PointF position, float buttonWidth = 75.0f, float buttonHeight = 75.0f); // Setup buttons here
	//~ButtonConsole();

	void Update(const PointF& mousePos);
    void Display();

	void LMBClicked( const PointF& mousePos ); // mouse clicked
	bool LMBReleased( const PointF& mousePos ); // mouse released  Returns true if button activated

	/*Returns the id of the button that was last focussed by hover */
	int GetChosenAction(); // Not const, as this clears ButtonID.

private:
    Renderer& renderer_;
    PointF position_; // position of first icon.

	int buttonID_; // current button that is hovered over.  a value less than 0 means no button

	float buttonWidth_, buttonHeight_;
	ButtonList buttons_;
	//PositionList btnPositions_;

	sf::Texture buttonTexture_;
};

#endif // BUTTON_H
