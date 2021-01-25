#pragma once

#include "../pch.h"

#include <Godot.hpp>
#include <Node2D.hpp>

#include "../../src/utils/Utils.h"

/**
 * Test the Player class's methods using godot and gtest
 */
class UtilsTest : public godot::Node2D {

	GODOT_CLASS(UtilsTest, godot::Node2D);

public:
	
	UtilsTest();
	~UtilsTest();

	

	/**
	 * Register the methods godot is directly going to call
	 */
	static void _register_methods();

	/**
	 * Run all tests at the scene initialisation
	 */
	void _init();	//Needed by godot

private:

	/* TESTS */

	void runAllTests();
	void testIsInsideRoom();
	void testIsInsideRoomX();
	void testIsInsideRoomY();
};