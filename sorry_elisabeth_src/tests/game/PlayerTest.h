#pragma once

#include "../pch.h"
#include "../../src/game/Player.h"

/**
 * Test the Player class's methods using godot and gtest
 */
class PlayerTest : public Player {

	GODOT_SUBCLASS(PlayerTest, Player);

public:
	
	PlayerTest();
	~PlayerTest();

	// Register the methods godot is directly going to call
	static void _register_methods();
	void _init(); //Needed by godot

	// Run all the test methods
	void _ready();

private:

	// Initialise the player attributes before testing
	void playerTestInit();
	void runAllTests();
	void changeDirectionTest();
};