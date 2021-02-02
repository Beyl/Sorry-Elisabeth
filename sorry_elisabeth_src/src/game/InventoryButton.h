#pragma once

#include <TextureButton.hpp>

#include "Inventory.h"
#include "FadeBackground.h"

class InventoryButton : public godot::TextureButton
{
	GODOT_CLASS(InventoryButton, godot::TextureButton);	// Needed by godot to be able to use this class

public:

	InventoryButton();
	~InventoryButton();

	// Register all methods and properties that godot is directly going to use and call
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	// Display OR hide the inventory and the fade background
	void on_button_released();

private:

	void displayAll();
	void hideAll();

	// Children nodes
	Inventory* m_inventory;
	FadeBackground* m_fadeBackground;
};