#pragma once

#include "../pch.h"
#include "../../src/game/InteractButton.h"

/**
 * Test the FadeBackground class's methods using godot and gtest
 */
class InteractButtonTest : public InteractButton {

	GODOT_SUBCLASS(InteractButtonTest, InteractButton);	// To make godot abble to use this class

public:
	
	InteractButtonTest();
	~InteractButtonTest();

	// Register the methods godot is directly going to call
	static void _register_methods();
	void _init(); //Needed by godot

	// Run all the test methods
	void _ready();

private:

	// Initialise the player attributes before testing
	void testIsDisplayed();
};