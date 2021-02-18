#pragma once

#include "ExamineInteraction.h"
#include "SearchPlace.h"
#include "FadeBackground.h"

#include <CanvasLayer.hpp>
#include <PackedScene.hpp>

/**
 * The interaction type : "Examine"
 		Display a dialog box and play the sound (voice) associated with it
 */
class OpenInteraction : public ExamineInteraction {

	GODOT_SUBCLASS(OpenInteraction, ExamineInteraction);	// Needed by godot to be able to use this class

public:

	OpenInteraction();
	~OpenInteraction();

	// Register the methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();
	
	// Play the examine interaction and display the search area
	virtual void play();


	/* SIGNALS */
	// Fade out the background
	void on_searchPlaceCloseButton_released();

	// Allow the player to close the search place window
	void on_dialogBoxHiding();

	// Emit the interaction_just_played signal again because the player hasn't finished interacting
	void on_examineInteraction_finished();

	void on_background_fadeOut_finished();


	/* PROPERTIES */
	void setSearchPlaceScene(const godot::Ref<godot::PackedScene> newSearchPlaceScene);
	godot::Ref<godot::PackedScene> getSearchPlaceScene() const;
	
	void setSearchPlaceSceneName(const godot::String newName);
	godot::String getSearchPlaceSceneName() const;

protected:

	//Children nodes
	SearchPlace* m_searchPlace;
	FadeBackground* m_searchPlaceBackground;

	// Properties
	godot::Ref<godot::PackedScene> m_searchPlaceScene;	//The specific search place the open interaction is going to open
	godot::String m_searchPlaceSceneName;	// Its node name
};