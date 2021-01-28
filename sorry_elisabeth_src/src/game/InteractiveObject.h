#pragma once

#include <Godot.hpp>
#include <AnimatedSprite.hpp>

#include "InteractionTable.h"
#include "InteractButton.h"
#include "ExamineInteraction.h"
#include "../utils/Utils.h"

class InteractiveObject : public godot::AnimatedSprite {

	GODOT_CLASS(InteractiveObject, godot::AnimatedSprite);	// Needed by godot to be able to use this class

public:

	InteractiveObject();
	~InteractiveObject();

	// Register all the methods and properties that godot is directly going to use and call
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	// Calculate the table position depending on the number of interactions in it
	void setInteractionTablePosition();

	void displayInteractButton();

	// Hide the interact button AND the interaction table
	void hideAll();
	
	// Determine if the interactive object is still offering interactions
	bool offerInteractions();

	// Set the next animation and the new interactions going with it
	void increaseState(godot::Array nextInteractions, Interaction* increaseTypeInteraction);


	/* SIGNALS */

	// Display the interaction table
	void on_interactButton_released();

	// Add the new interactions to the interaction table
	void on_increaseTypeInteraction_finished();


	/* PROPERTIES */

	int m_objectStateNumber;
	void setObjectStateNumber(int stateNumber);
	int getObjectStateNumber();

	godot::Vector2 m_objectSize;
	void setObjectSize(godot::Vector2 newSize);
	godot::Vector2 getObjectSize();


	/* CONSTANTS */

	// 49 on ascii table is equal to "1"
	const int ASCII_CONVERSION_1 = 49;

protected:

	// Child nodes
	InteractButton* m_interactButton;
	InteractionTable* m_interactionTable;

	int m_state;
};