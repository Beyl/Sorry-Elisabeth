#pragma once

#include "ExamineInteraction.h"
#include "MainScene.h"

/**
 * Represents a unique interaction in the game, when the player takes up the handbag.
		It makes the inventory grow up, and change the player's sprite animation.
 */
class TakeHandbagInteraction : public ExamineInteraction {

	GODOT_SUBCLASS(TakeHandbagInteraction, ExamineInteraction);

public:

	TakeHandbagInteraction();
	~TakeHandbagInteraction();

	static void _register_methods();
	void _init();

	void _ready();

	// Grow up the inventory, change player's sprite animations, remove the handbag and play the examine interaction going with it
	void play();


	/* PROPERTIES */
	void setPlayerAbsolutePath(const godot::String newPath);
	godot::String getPlayerAbsolutePath() const;

	void setInventoryAboslutePath(const godot::String newPath);
	godot::String getInventoryAboslutePath() const;

private:

	Player* m_player;
	Inventory* m_inventory;

	// Properties
	godot::String m_playerAbsolutePath;
	godot::String m_inventoryAbsolutePath;
};