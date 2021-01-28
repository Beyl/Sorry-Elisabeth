#pragma once

#include <Godot.hpp>
#include <TextureButton.hpp>
#include <Label.hpp>
#include <Tween.hpp>
#include <AudioStreamPlayer2D.hpp>
#include <AudioStreamSample.hpp>

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

	// Initilisation of the class and the godot scene
	void _ready();

	// Play the interaction (no specific function to do here, that's why it is a pure virtual method)
	virtual void play() = 0;
	
	// Play the object sound if there's one setted
	void on_button_released();


	/* PROPERTIES */

	// The text that will be displayed representing the interaction's name
	godot::String m_interactionName;
	void setInteractionName(godot::String newName);
	godot::String getInteractionName();

	// The possible sound associated with the interaction
	godot::Ref<godot::AudioStreamSample> m_objectSound;
	void setObjectSound(godot::Ref<godot::AudioStreamSample> newSound);
	godot::Ref<godot::AudioStreamSample> getObjectSound();
	

	/* CONSTANTS */
	static const int MAX_NAME_CHAR = 18;

protected:

	//Child nodes
	godot::Label* m_label;
	godot::AudioStreamPlayer2D* m_objectSoundPlayer;
};