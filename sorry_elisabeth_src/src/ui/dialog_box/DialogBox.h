#pragma once

#include <Godot.hpp>
#include <TextureRect.hpp>
#include <RichTextLabel.hpp>
#include <Tween.hpp>
#include <Timer.hpp>

#include "../../utils/Utils.h"

class DialogBox : public godot::TextureRect {

	GODOT_CLASS(DialogBox, godot::TextureRect);

public:
	/* CONSTRUCTOR & DESTRUCTOR */

	/**
	 * Constructor of the class, create the class and avoid warnings.
	 *		The real initialisation takes place in the "_ready" method.
	 */
	DialogBox();

	/**
	 * Destructor of the class, not usefull here, godot manages the memory itself. 
	 */
	~DialogBox();

	/* METHODS */

	/**
	 * Register the methods that godot is directly going to call.
	 */
	static void _register_methods();

	/**
	 * Needed by godot to create the class, not usefull here.
	 */
	void _init();

	/**
	 * Initalise the class and the godot scene.
	 */
	void _ready();

	/**
	 * Display the dialog box on the screen with a smooth animation
	 */
	void display();

	/**
	 * Display the text inside the box with a smooth linear animation
	 */
	void displayText();

	/**
	 * Hide the dialog box with a smooth animation
	 */
	void hide();

	//SIGNALS

	/**
	 * Called when the timer reach 0
	 */
	void on_beforeHideTimer_timeout();

	/**
	 * Called when the text has been entirely displayed.
	 *		Start the beforeHide timer.
	 */
	void on_textDisplayed();

	/* PROPERTIES */

	double m_textDisplayDuration;

	/**
	 * Set the text display duration.
	 * 
	 * @param newDuration the new display duration
	 */
	void setTextDisplayDuration(double newDuration);

	/**
	 * Set the text display duration.
	 *
	 * @return the text display duration
	 */
	double getTextDisplayDuration();

	double m_transitionDisplayDuration;

	/**
	 * Set the transition display duration.
	 *
	 * @param newDuration the new transition duration
	 */
	void setTransitionDisplayDuration(double newDuration);

	/**
	 * Set the transition display duration.
	 *
	 * @return the transition duration
	 */
	double getTransitionDisplayDuration();

private:
	//Children nodes
	godot::RichTextLabel* m_textLabel;
	godot::Timer* m_beforeHideTimer;
	godot::Tween* m_boxTween;
	godot::Tween* m_textTween;

	godot::Vector2 m_displayPosition;
	godot::Vector2 m_hidePosition;
};