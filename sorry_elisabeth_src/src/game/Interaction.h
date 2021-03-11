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
 *		It's a button that make the interaction table disapear when clicked.
 *		The extensions of this class will define specific actions depending on the interaction type.
 * version 0.0
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
	void setInteractionName(const godot::String newName);
	godot::String getInteractionName() const;

	void setObjectSound(const godot::Ref<godot::AudioStreamSample> newSound);
	godot::Ref<godot::AudioStreamSample> getObjectSound() const;
	

	/* CONSTANTS */
	static const int MAX_NAME_CHAR = 18;
	const godot::NodePath PARENT_INTERACTIVE_OBJECT_PATH = "../../..";
	static const int MAX_INTERACTIONS_NUMBER = 3;
	static const int INTERACT_BUTTON_MARGIN = 1;

protected:

	// Children nodes
	godot::Label* m_label;
	godot::AudioStreamPlayer2D* m_objectSoundPlayer;

	// Properties
	godot::Ref<godot::AudioStreamSample> m_objectSound;	// The possible sound associated with the interaction
	godot::String m_interactionName;	// The text that will be displayed representing the interaction's name
};