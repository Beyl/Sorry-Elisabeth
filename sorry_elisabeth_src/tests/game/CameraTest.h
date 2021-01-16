#include "../pch.h"

#include <Godot.hpp>
#include <Node2D.hpp>

#include "../../src/game/Camera.h"

/**
 * Test the Player class's methods using godot and gtest
 */
class CameraTest : public godot::Node2D {

	GODOT_CLASS(CameraTest, godot::Node2D);

public:
	/* CONSTRUCTOR & DESTRUCTOR */

	/**
	 * Constructor, usefull only to create an instance and avoid warnings,
	 *		the initialisation is done in the "_ready" method.
	 */
	CameraTest();

	/**
	 * Destructor, usefull only to create the class and avoid warnings,
	 *		godot deallocates the memory itself.
	 */
	~CameraTest();

	/* METHODS */

	//Needed by godot

	/**
	 * Register the methods godot is directly going to call
	 */
	static void _register_methods();

	/**
	 * Needed by godot to create the class, not usefull here
	 *		the initialisation is done in the "_ready" method called after
	 *
	 */
	void _init();

	/**
	 * Initilisation of the class and the scene
	 *		called after the parent node and all its children entenred a scene.
	 */
	void _ready();

private:

	/* TESTS */

	/**
	 * Run all the tests methods
	 */
	void runAllTests();

	/**
	 * "isPlayerInsideChangeRoomRangeTest" method tests
	 */
	void isPlayerInsideChangeRoomRangeTest();

	/**
	 * "isPlayerEnteringNewRoom" method tests
	 */
	void isPlayerEnteringNewRoomTest();

	Camera* m_camera;
};