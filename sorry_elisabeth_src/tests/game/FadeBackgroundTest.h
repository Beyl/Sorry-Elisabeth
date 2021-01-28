#pragma once

#include "../pch.h"
#include "../../src/game/FadeBackground.h"

/**
 * Test the FadeBackground class's methods using godot and gtest
 */
class FadeBackgroundTest : public FadeBackground {

	GODOT_SUBCLASS(FadeBackgroundTest, FadeBackground);	// To make godot abble to use this class

public:
	
	FadeBackgroundTest();
	~FadeBackgroundTest();

	// Register the methods godot is directly going to call
	static void _register_methods();
	void _init(); // Needed by godot

	// Run all the test methods
	void _ready();

private:

	// Initialise the player attributes before testing
	void testIsDisplayed();
};