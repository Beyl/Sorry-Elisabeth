#pragma once

#include "Interaction.h"
#include "DialogBox.h"

#include <AudioStreamPlayer.hpp>
#include <AudioStream.hpp>
#include <Ref.hpp>

/**
 * The interaction type : "Examine"
 *		Display a dialog box and play the sound (voice) associated with it
 */
class ExamineInteraction : public Interaction {

	GODOT_CLASS(ExamineInteraction, godot::TextureButton);	//To make godot able to use this class

public:

	ExamineInteraction();
	~ExamineInteraction();

	// Register the methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	//Needed by godot

	// Initialise the class and the godot scene
	void _ready();
	
	// Display the dialog box and the play the sound (voice) associated with it
	virtual void play();

	// Play the interaction
	void on_button_released();


	/* PROPERTIES */

	godot::String m_examineText;	//Text that will be displayed in the dialog box
	void setExamineText(godot::String newText);
	godot::String getExamineText();

	godot::Ref<godot::AudioStreamSample> m_examinationSound;
	void setExaminationSound(godot::Ref<godot::AudioStreamSample> newSound);
	godot::Ref<godot::AudioStreamSample> getExaminationSound();

protected:

	//Child nodes
	DialogBox* m_dialogBox;
	godot::AudioStreamPlayer* m_examinationSoundPlayer;
};