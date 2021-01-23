#pragma once

#include <Godot.hpp>
#include <TextureRect.hpp>
#include <RichTextLabel.hpp>
#include <Tween.hpp>
#include <Timer.hpp>

#include "../../utils/Utils.h"

/**
 * Represents a box that displays text on the screen.
 */
class DialogBox : public godot::TextureRect {

	GODOT_CLASS(DialogBox, godot::TextureRect);	//To make godot able to use this class

public:

	DialogBox();
	~DialogBox();

	/**
	 * Register the methods and properties that godot is directly going to call and use
	 */
	static void _register_methods();

	void _init();	//Needed by godot

	/**
	 * Initalise the class and the scene.
	 */
	void _ready();

	/*
	 * Display the dialog box on the screen with a smooth animation
	 */
	void display();

	/**
	 * Set the text that will be displayed in the rich label text
	 */
	void setDisplayedText(godot::String displayedText);

	godot::Vector2 getDisplayPosition();

	/* SIGNALS */

	/**
	 * Hide the dialog box
	 */
	void on_beforeHideTimer_timeout();

	/**
	 * Start the beforeHide timer
	 */
	void on_textDisplayed();

	/**
	 * Display the text
	 */
	void on_displayAnimation_completed();

	/* PROPERTIES */

	double m_textDisplayDuration;
	void setTextDisplayDuration(double newDuration);
	double getTextDisplayDuration();


	double m_transitionDisplayDuration;
	void setTransitionDisplayDuration(double newDuration);
	double getTransitionDisplayDuration();

private:

	/**
	 * Display the text inside the box with a smooth animation
	 */
	void displayText();

	/**
	 * Hide the dialog box with a smooth animation
	 */
	void hide();
	


	/* MEMBER VARIABLES */

	//Children nodes
	godot::RichTextLabel* m_textLabel;
	godot::Timer* m_beforeHideTimer;
	godot::Tween* m_boxTween;
	godot::Tween* m_textTween;

	godot::Vector2 m_displayPosition;
	godot::Vector2 m_hidePosition;


	/* CONSTANTS */
	static const int MIN_TEXT_DISPLAY_DURATION = 1;
	static const int MIN_TRANSITION_DISPLAY_DURATION = 1;
	static const int X_DISPLAY_POSITION = 20;
	static const int Y_DISPLAY_POSITION = 145;
};