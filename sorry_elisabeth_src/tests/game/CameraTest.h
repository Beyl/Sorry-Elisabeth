#pragma once

#include "../pch.h"
#include "../../src/game/Camera.h"

/**
 * Test the Camera class's methods using godot and gtest
 */
class CameraTest : public Camera {

	GODOT_SUBCLASS(CameraTest, Camera);

public:
	
	CameraTest();
	~CameraTest();

	// Register the methods godot is directly going to call
	static void _register_methods();
	void _init();	//Needed by godot

	// Run all the test methods
	void _ready();

private:

	void runAllTests();
	void isPlayerInsideChangeRoomRangeTest();
	void isPlayerEnteringNewRoomTest();
};