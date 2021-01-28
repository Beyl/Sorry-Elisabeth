#pragma once

#include <Godot.hpp>
#include <TextureRect.hpp>
#include <RichTextLabel.hpp>
#include <Tween.hpp>
#include <Timer.hpp>

#include "../utils/Utils.h"

/**
 * Represents a box that displays text on the screen.
 */
class DialogBox : public godot::TextureRect {

	GODOT_CLASS(DialogBox, godot::TextureRect);	//To make godot able to use this class

public:

	DialogBox();
	~DialogBox();

	// Register the methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	//Needed by godot

	// Initalise the class and the godot scene
	void _ready();

	void display();
	void hide();
	bool isHided();

	// Set the text that will be displayed in the box
	void setDisplayedText(godot::String displayedText);


	/* ACCESSORS */
	godot::Vector2 getDisplayPosition();
	godot::Timer* getBeforeHideTimer();


	/* SIGNALS */

	// Hide the dialog box
	void on_beforeHideTimer_timeout();

	// Starts the beforeHide timer
	void on_textDisplayed();

	// Display the text
	void on_displayAnimation_completed();

	// Emit finished signal
	void on_hideAnimation_completed();


	/* PROPERTIES */

	real_t m_textDisplayDuration;
	void setTextDisplayDuration(real_t newDuration);
	real_t getTextDisplayDuration();

	real_t m_transitionDisplayDuration;
	void setTransitionDisplayDuration(real_t newDuration);
	real_t getTransitionDisplayDuration();

	//Time in second before starting the hiding duration, after the text has been displayed
	real_t m_beforeHidingDuration;
	void setBeforeHidingDuration(real_t newDuration);
	real_t getBeforeHidingDuration();


	/* CONSTANTS */

	static const int MIN_TEXT_DISPLAY_DURATION = 1;
	static const int MIN_TRANSITION_DISPLAY_DURATION = 1;
	static const int MIN_BEFORE_HIDING_DURATION = 1;
	static const int X_DISPLAY_POSITION = 20;
	static const int Y_DISPLAY_POSITION = 145;

protected:

	//Children nodes
	godot::RichTextLabel* m_textLabel;
	godot::Timer* m_beforeHideTimer;
	godot::Tween* m_boxTween;
	godot::Tween* m_textTween;

	godot::Vector2 m_displayPosition;
	godot::Vector2 m_hidePosition;
};