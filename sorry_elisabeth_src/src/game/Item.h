#pragma once

#include "InteractiveObject.h"

/**
 * Represents inventory's items wich the player will be able to interact with
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
	

	/* ACCESSORS */
	InteractionTable* getInteractionTable() const;
	InteractButton* getInteractButton() const;


	/* SIGNALS */
	// Display the interaction table
	void on_interactButton_released();

	void on_interaction_just_played();
	void on_interaction_finished();

	/* CONSTANT */
	static const int ITEM_SIZE = 10;

private:
	// Calculate and set the interaction table's position depending on its size
	void setInteractionTablePosition();
};