#pragma once

#include "../pch.h"

#include <Godot.hpp>
#include <Node2D.hpp>

#include "../../src/utils/Utils.h"

class UtilsTest : public godot::Node2D {

	GODOT_CLASS(UtilsTest, godot::Node2D);

public:
	/* CONSTRUCTOR & DESTRUCTOR */

	/**
	 * Constructor, usefull only to create an instance and avoid warnings,
	 *		the initialisation is done in the "_init" method.
	 */
	UtilsTest();

	/**
	 * Destructor, usefull only to create the class and avoid warnings,
	 *		godot deallocates the memory itself.
	 */
	~UtilsTest();

	/* METHODS */

	//Needed by godot

	/**
	 * Register the methods godot is directly going to call
	 */
	static void _register_methods();

	/**
	 * Call "runAllTests"
	 */
	void _init();

private:

	/* TESTS */

	/**
	 * Run all the test's methods
	 */
	void runAllTests();

	/**
	 * "isInsideRoom" method test
	 */
	void testIsInsideRoom();

	/**
	 * "isInsideRoomX" method test
	 */
	void testIsInsideRoomX();

	/**
	 * "isInsideRoomY" method test
	 */
	void testIsInsideRoomY();
};