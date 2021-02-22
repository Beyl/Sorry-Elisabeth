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

	GODOT_CLASS(DialogBox, godot::TextureRect);	// To make godot able to use this class

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
	bool isHided() const;

	// Set the text that will be displayed in the box
	void setDisplayedText(const godot::String displayedText);
	godot::String getDisplayedText() const;


	/* ACCESSORS */
	godot::Vector2 getDisplayPosition() const;
	godot::Timer* getBeforeHideTimer() const;


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
	void setTextDisplayDuration(const real_t newDuration);
	real_t getTextDisplayDuration() const;

	void setTransitionDisplayDuration(const real_t newDuration);
	real_t getTransitionDisplayDuration() const;

	void setBeforeHidingDuration(const real_t newDuration);
	real_t getBeforeHidingDuration() const;


	/* CONSTANTS */
	static const int MIN_TEXT_DISPLAY_DURATION = 1;
	static const int MIN_TRANSITION_DISPLAY_DURATION = NULL;
	static const int MIN_BEFORE_HIDING_DURATION = NULL;
	static const int X_DISPLAY_POSITION = 20;
	static const int Y_DISPLAY_POSITION = 155;

protected:

	// Children nodes
	godot::RichTextLabel* m_textLabel;
	godot::Timer* m_beforeHideTimer;
	godot::Tween* m_boxTween;
	godot::Tween* m_textTween;

	godot::Vector2 m_displayPosition;
	godot::Vector2 m_hidePosition;

	// Properties
	real_t m_textDisplayDuration;
	real_t m_transitionDisplayDuration;
	real_t m_beforeHidingDuration;	// Time in second before starting the hiding duration, after the text has been displayed
};