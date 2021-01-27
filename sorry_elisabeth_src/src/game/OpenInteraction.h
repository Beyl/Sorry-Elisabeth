#pragma once

#include "ExamineInteraction.h"
#include "SearchPlace.h"
#include "FadeBackground.h"

#include <CanvasLayer.hpp>
#include <PackedScene.hpp>

/**
 * The interaction type : "Examine"
 *		Display a dialog box and play the sound (voice) associated with it
 */
class OpenInteraction : public ExamineInteraction {

	GODOT_SUBCLASS(OpenInteraction, ExamineInteraction);	//To make godot able to use this class

public:

	OpenInteraction();
	~OpenInteraction();

	// Register the methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	//Needed by godot

	// Initialise the class and the godot scene
	void _ready();
	
	// Play the examine interaction and display the search area
	virtual void play();

	// Fade out the background
	void on_searchPlaceCloseButton_released();

	// Allow the player to close the search place window
	void on_dialogBoxHiding();


	/* PROPERTIES */

	//The specific search place the open interaction is going to open
	godot::Ref<godot::PackedScene> m_searchPlaceScene;
	void setSearchPlaceScene(godot::Ref<godot::PackedScene> newSearchPlaceScene);
	godot::Ref<godot::PackedScene> getSearchPlaceScene();
	
	//Its node name
	godot::String m_searchPlaceSceneName;
	void setSearchPlaceSceneName(godot::String newName);
	godot::String getSearchPlaceSceneName();

protected:

	//Children nodes
	SearchPlace* m_searchPlace;
	FadeBackground* m_searchPlaceBackground;
};