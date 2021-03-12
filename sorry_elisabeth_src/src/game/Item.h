#pragma once

#include "InteractiveObject.h"

/**
 * Represents inventory's items wich the player will be able to interact with.
 * @version 0.0
 */
class Item : public InteractiveObject {

	GODOT_SUBCLASS(Item, InteractiveObject);	// Needed by godot to be able to use this class

public:

	Item();
	~Item();

	// Register all the methods and properties that godot is directly going to use and call
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();
	
	// Used only in an open interaction situation. Handle interactions
	void _process(float delta);

	// Enable the process method
	void enableOpenMode();
	void disableOpenMode();


	/* ACCESSORS & MUTATORS */
	InteractionTable* getInteractionTable() const;
	InteractButton* getInteractButton() const;
	void setPlayerIsInteracting(const bool isInteracting);


	/* SIGNALS */
	// Display the interaction table
	void on_interactButton_released();

	void on_interaction_table_displayed();

	void on_interaction_just_played();
	void on_interaction_finished();

	/* CONSTANT */
	static const int ITEM_SIZE = 10;

private:
	// Calculate and set the interaction table's position depending on its size
	void setInteractionTablePosition();

	bool m_isPlayerInteracting;	// Usefull only in open mode
};