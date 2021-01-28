#pragma once

#include "../pch.h"
#include "../../src/game/DialogBox.h"

/**
 * Test the Player class's methods using godot and gtest
 */
class DialogBoxTest : public DialogBox {

	GODOT_SUBCLASS(DialogBoxTest, DialogBox);

public:
	
	DialogBoxTest();
	~DialogBoxTest();

	// Register the methods godot is directly going to call
	static void _register_methods();
	void _init(); // Needed by godot

	// Run all the test methods
	void _ready();

private:

	// Initialise the player attributes before testing
	void testIsHided();
};