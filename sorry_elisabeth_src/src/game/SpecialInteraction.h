#pragma once

#include "ExamineInteraction.h"
#include "FadeBackground.h"
#include "InteractiveObject.h"

#include <Timer.hpp>

/**
 * Represents a bunch of specific interactions that makes the interactive objects associated increase its state.
 * @version 0.0
 */
class SpecialInteraction : public ExamineInteraction {

	GODOT_SUBCLASS(SpecialInteraction, ExamineInteraction);	// Needed by godot to be able to use this class

public:

	SpecialInteraction();
	~SpecialInteraction();

	// Register the methods and properties that godot is directly going to use and call
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	/** 
	 * Play the special interaction :
	 *		- Fade in and out to a black screen
	 *		- Play the special interaction sound
	 *		- Increase the parent interactive object state
	 */
	void play();
	

	/* SIGNALS */
	// Play the sound and increase it's parent interactive object state (next animation + next interactions)
	void on_fadeIn_finished();
	
	// Start fading out
	void on_specialSound_played();
	
	// Play the examine interaction associated with the special interaction
	void on_fadeOut_finished();


	/* PROPERTIES */
	void setSpecialSound(const godot::Ref<godot::AudioStreamSample> newSound);
	godot::Ref<godot::AudioStreamSample> getSpecialSound() const;

	void setNextInteractions(const godot::Array newInteractions);
	godot::Array getNextInteractions() const;

protected:

	// Children nodes
	FadeBackground* m_fadeBackground;
	godot::AudioStreamPlayer* m_specialSoundPlayer;

	// Properties
	godot::Ref<godot::AudioStreamSample> m_specialSound;
	godot::Array m_nextInteractions{};
};