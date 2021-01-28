#pragma once

#include "../pch.h"
#include "../../src/game/InteractiveObject.h"

/**
 * Test the FadeBackground class's methods using godot and gtest
 */
class InteractiveObjectTest : public InteractiveObject {

	GODOT_SUBCLASS(InteractiveObjectTest, InteractiveObject);	// To make godot abble to use this class

public:
	
	InteractiveObjectTest();
	~InteractiveObjectTest();

	// Register the methods godot is directly going to call
	static void _register_methods();
	void _init(); //Needed by godot

	// Run all the test methods
	void _ready();

private:

	// Initialise the player attributes before testing
	void testOfferInteractions();
};