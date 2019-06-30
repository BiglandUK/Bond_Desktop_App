// Button.cpp

#include "Button.h"
#include <algorithm>
//#include "SpriteManagement.h"
//#include "Renderer.h"
#include <iostream>
using namespace std;

Button::Button()
: value_(0), width_(0), height_(0), state_(ButtonState::Normal), text_("")
{}

Button::Button(int value, int width, int height)
: value_(value), width_(width), height_(height), state_(ButtonState::Normal)
{}

void Button::SetState( const ButtonState& state ){
	state_ = state;
}

ButtonState Button::GetState() const {
	return state_;
}

void Button::Reset() { state_ = ButtonState::Normal;}
void Button::Select() { state_ = ButtonState::Selected; }
void Button::Disable() { state_ = ButtonState::Disabled; }

void Button::SetDimensions( const int width, const int height ){
    if( width > 0 ) width_ = width;
    if( height > 0 ) height_ = height;
}

int Button::GetWidth() const { return width_; }
int Button::GetHeight() const{ return height_; }

void Button::SetIcon(const sf::Sprite& icon) { icon_ = icon; }
const sf::Sprite& Button::GetIcon() const{ return icon_; }
void Button::SetIconPosition(int x, int y) { iconPos_.x = x; iconPos_.y = y; }
const sf::Vector2i& Button::GetIconPosition() const { return iconPos_; }

void Button::SetText(const std::string& text) { text_ = text; }
const std::string& Button::GetText() const { return text_; }
void Button::SetTextPosition(int x, int y) { textPos_.x = x; textPos_.y = y; }
const sf::Vector2i& Button::GetTextPosition() const { return textPos_; }

void Button::SetValue(int value) { value_ = value; }
int Button::Value() const { return value_; }


ButtonConsole::ButtonConsole()
{
 

}

void ButtonConsole::AddButton(int value, std::string text) {
	buttons_.push_back(Button(value, 0, 0 ));
	buttons_.back().SetText(text);
}

void ButtonConsole::Update(const PointF& mousePos) {
    //int id = 0; // identify current button
    //for( auto& b : buttons_ ){
    //    if( PointInsideRegionF( mousePos, b.GetPosition(), buttonWidth_, buttonHeight_ ) ){
    //        // Mouse is positioned over a button
    //        if( buttonID_ != id ){ // This is a different button than before
    //            if( buttonID_ < 0 ){// No button currently stored
    //                buttonID_ = id;
    //                b.SetState( Hover );
    //            } else if( b.GetState() != Depress ){
    //                // The previously stored button is not pressed.
    //                buttons_[buttonID_].SetState();
    //                buttonID_ = id;
    //                b.SetState(Hover);
    //            }
    //        }
    //    } else { // No button
    //        b.SetState();
    //        if( buttonID_ == id ) // This button was hovered
    //            buttonID_ = -1;  // but not now.
    //    }
    //    ++id; // identifier for next button
    //}
}

void ButtonConsole::Display(){
 //   for( const Button& b : buttons_ ){
 //       renderer_.Display(b);
 //   }
 //   // Display the tooltip
	//if( buttonID_ >= 0 ){
 //       renderer_.DisplayCentredText( buttons_[buttonID_].GetTooltip() );
	//}
}

void ButtonConsole::Click(const PointF& mousePos) {
    //for( Button& b : buttons_ ){
    //    b.SetState( Normal );
    //    if( PointInsideRegionF( mousePos, b.GetPosition(), buttonWidth_, buttonHeight_ ) ){
    //        b.SetState( Depress );
    //    }
    //}
}

bool ButtonConsole::Release( const PointF& mousePos ){
	// If the mouse is still over the button in a click state
	//if( buttonID_ < 0 ) return false;
	//if( PointInsideRegion( mousePos, buttons_[buttonID_].GetPosition(), buttonWidth_, buttonHeight_ ) ){
	//    if( buttons_[buttonID_].GetState() != Depress ) // button must be clicked first!
	//        return false;
	//    buttons_[buttonID_].SetState();
	//    return true;
	//}
	//buttons_[buttonID_].SetState();
	//buttonID_ = -1;
	return false;
}

int ButtonConsole::GetChosenAction(){
    //int action = buttonID_;
    //buttonID_ = -1;
    return -1;
}

void ButtonConsole::DisplayButtons() {
	for (auto b : buttons_) {
		std::cout << b.GetText() << " value:" << b.Value() << std::endl;
	}
}