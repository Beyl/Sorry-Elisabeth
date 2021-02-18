#pragma once

#include <AnimationPlayer.hpp>

#include "Inventory.h"
#include "FadeBackground.h"

class Inventory;

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
	
	// Manage mouse filter
	void _process(float delta);

	// Display OR hide the inventory and the fade background
	void on_button_released();

	// Play the interation signal animation
	void on_Inventory_interact();

	// Hide the button under the bottom of the screen
	void hideButton();

	// Display the button
	void displayButton();

	bool isInventoryOpen();


	/* SIGNALS */
	void on_tween_all_completed();


	/* PROPERTIES */
	void setDisplayPosition(const godot::Vector2 position);
	godot::Vector2 getDisplayPosition() const;

	void setHidePosition(const godot::Vector2 position);
	godot::Vector2 getHidePosition() const;


	/* CONSTANT */
	const real_t TWEEN_ANIMATION_DURATION = 0.75;
	const godot::Vector2 INVENTORY_GLOBAL_POSITION = godot::Vector2(42, 60);

private:

	void displayAll();
	void hideAll();

	// Children nodes
	Inventory* m_inventory;
	FadeBackground* m_fadeBackground;
	godot::AnimationPlayer* m_animationPlayer;
	godot::Tween* m_tween;

	godot::Vector2 m_displayPosition;
	godot::Vector2 m_hidePosition;
	bool m_isAnimated;
	bool m_isDisplaying;
};