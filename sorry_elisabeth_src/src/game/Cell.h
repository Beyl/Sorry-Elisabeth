#pragma once

#include <Godot.hpp>
#include <TextureButton.hpp>

#include "Item.h"

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
	void _process();

	// Set the new item and remove the ex one
	void setItem(Item* newItem);
	Item* getItem() const;

	// Determine if the cell contain an item or not
	bool containItem() const;


	/* CONSTANTS */
	static const int HIDE_INTERACT_BUTTON_MARGIN_X = 4;
	static const int HIDE_INTERACT_BUTTON_MARGIN_Y = 16;

protected:

	// Children nodes
	Item* m_item;
	InteractionTable* m_itemInteractionTable;
	InteractButton* m_itemInteractButton;
};