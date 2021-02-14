#pragma once

#include "ExamineInteraction.h"
#include "Player.h"
#include "Inventory.h"

/**
 * Represents a unique interaction in the game, when the player takes up the handbag.
		It makes the inventory grow up, and change the player's sprite animation.
 */
class TakeHandbagInteraction : public ExamineInteraction {

	GODOT_SUBCLASS(TakeHandbagInteraction, ExamineInteraction);	// Needed by godot to be able to use this class

public:

	TakeHandbagInteraction();
	~TakeHandbagInteraction();

	// Register all methods and properties that godot is directly going to call and use
	static void _register_methods();
	// Manage groups
	void _init();

	// Grow up the inventory, change player's sprite animations, remove the handbag and play the examine interaction going with it
	virtual void play();


	/* SIGNAL */
	void on_examineInteraction_finished();


	/* MUTATORS */
	void setPlayer(Player* newPlayer);
	void setInventory(Inventory* newInventory);

private:

	Player* m_player;
	Inventory* m_inventory;
};