#pragma once

#include "../pch.h"
#include "../../src/game/InteractionTable.h"

/**
 * Test the FadeBackground class's methods using godot and gtest
 */
class InteractionTableTest : public InteractionTable {

	GODOT_SUBCLASS(InteractionTableTest, InteractionTable);	// To make godot abble to use this class

public:
	
	InteractionTableTest();
	~InteractionTableTest();

	// Register the methods godot is directly going to call
	static void _register_methods();
	void _init(); //Needed by godot

	// Run all the test methods
	void _ready();

private:

	// Initialise the player attributes before testing
	void testGetInteractionsNumber();
};