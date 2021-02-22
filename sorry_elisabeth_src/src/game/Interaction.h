#pragma once

#include <Godot.hpp>
#include <TextureButton.hpp>
#include <Tween.hpp>

/**
 * Mother class (pure virtual) of all the interactions.
 * 
 * It's a button that make the interaction table disapear when clicked.
 * The extensions of this class will define specific actions depending on the interaction type.
 */
class Interaction : public godot::TextureButton {

public:
	/* CONSTRUCTOR && DESTRUCTOR */

	/**
	 * Constructor, usefull only to create the class and avoid warnings,
	 *		the real initialisation is done in the "_ready" method.
	 */
	Interaction();

	/**
	 * Destructor, usefull only to create the class and avoid warnings,
	 *		godot deallocates the memory itself.
	 */
	~Interaction();

	/* METHODS */

	//Needed by godot

	/**
	 * Register the methods godot is directly going to call
	 */
	void _register_methods();

	/**
	 * Initilisation of the class and the scene
	 *		called after the parent node and all its children entenred a scene.
	 */
	void _ready();

	/**
	 * Play the interaction
	 */
	virtual void play() = 0;
	
	/**
	 * Call "hideParent".
	 *		Called when the left mouse button is released.
	 */
	virtual void on_button_released();

	/**
	 * Hide the parent (interaction table) with a smooth animation
	 */
	void hideParent();

	/* PROPERTIES */

	double m_hidingDuration;
	void setHidingDuration(double newDuration);
	double getHidingDuration();
	
protected:
	//Child nodes
	godot::Tween* m_tween;
};