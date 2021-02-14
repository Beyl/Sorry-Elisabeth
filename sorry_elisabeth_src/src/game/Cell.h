#pragma once

#include "Item.h"

/**
 *	Represents a cell in the inventory.
		Can contain an item.
 */
class Cell : public godot::TextureButton {

	GODOT_CLASS(Cell, godot::TextureButton);	// Needed by godot to be able to use this class

public:

	Cell();
	~Cell();

	// Register all the methods and properties that godot is directly going to use and call
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	// Called every frame, manage user actions
	void _process(float delta);

	// Set the new item and remove the ex one
	void setItem(Item* newItem);
	Item* getItem() const;

	// Determine if the cell contain an item or not
	bool containItem() const;

	void enableInteractions();
	void disableInteractions();

	// Disable the display and the use of the interact button and the interaction table
	void enableSpecialMode();
	// Enable the display and the use of the interact button and of the interaction table
	void disableSpecialMode();


	/* SIGNALS */
	void on_button_up();


	/* CONSTANTS */
	const godot::NodePath INVENTORY_LOCAL_PATH = "../..";
	static const int HIDE_INTERACT_BUTTON_MARGIN_X = 4;
	static const int HIDE_INTERACT_BUTTON_MARGIN_Y = 16;

protected:

	// Children nodes
	Item* m_item;
	InteractionTable* m_itemInteractionTable;
	InteractButton* m_itemInteractButton;

	bool m_isInSpecialMode;
	bool m_canInteract;
};