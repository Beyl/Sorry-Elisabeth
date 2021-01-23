#pragma once

#include <Godot.hpp>
#include <TextureButton.hpp>
#include <Label.hpp>
#include <Tween.hpp>

#include "../utils/Utils.h"

/**
 * Mother class (abstract) of all the interactions.
 * 
 * It's a button that make the interaction table disapear when clicked.
 * The extensions of this class will define specific actions depending on the interaction type.
 */
class Interaction : public godot::TextureButton {

public:

	Interaction();
	~Interaction();

	/**
	 * Initilisation of the class and the scene.
	 */
	void _ready();

	/**
	 * Play the interaction (no specific function to do here, that's why it is a pure virtual method)
	 */
	virtual void play() = 0;
	
	/**
	 * Hide the parent (an interaction table)
	 */
	void on_button_released();



	/* PROPERTIES */

	double m_hidingDuration;
	void setHidingDuration(double newDuration);
	double getHidingDuration();

	godot::String m_interactionName;
	void setInteractionName(godot::String newName);
	godot::String getInteractionName();
	
protected:

	/**
	 * Hide the parent (interaction table) with a smooth animation
	 */
	void hideParent();



	/* MEMBER VARIABLES */

	//Child nodes
	godot::Tween* m_tween;
	godot::Label* m_label;



	/* CONSTANTS */

	static const int MAX_NAME_CHAR = 18;
};