#pragma once

#include <TextureButton.hpp>
#include <AnimationPlayer.hpp>

#include "Inventory.h"
#include "FadeBackground.h"

/**
 * Represents the button that display or hide the player's inventory.
 */
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

	// Play the interation signal animation
	void on_Inventory_interact();

private:

	void displayAll();
	void hideAll();

	// Children nodes
	Inventory* m_inventory;
	FadeBackground* m_fadeBackground;
	godot::AnimationPlayer* m_animationPlayer;
};