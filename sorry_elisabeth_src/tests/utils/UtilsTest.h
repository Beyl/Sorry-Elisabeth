#pragma once

#include "../pch.h"

#include <Node2D.hpp>

#include "../../src/utils/Utils.h"
#include "../../src/game/Inventory.h"

/**
 * Test the Utils class's methods AND other static methods using godot and gtest
 */
class UtilsTest : public godot::Node2D {

	GODOT_CLASS(UtilsTest, godot::Node2D);

public:
	
	UtilsTest();
	~UtilsTest();

	// Register the methods godot is directly going to call
	static void _register_methods();

	// Run all tests
	void _init();	// Needed by godot

private:

	void runAllTests();
	void testIsInsideRoom();
	void testIsInsideRoomX();
	void testIsInsideRoomY();
	void testGetCenteredPosition();
};