#include "../pch.h"

#include <Godot.hpp>
#include <Node2D.hpp>

#include "../../src/game/Player.h"

/**
 * Test the Player class's methods using godot and gtest
 */
class PlayerTest : public Player {

	GODOT_SUBCLASS(PlayerTest, Player);

public:
	
	PlayerTest();
	~PlayerTest();



	/**
	 * Register the methods godot is directly going to call
	 */
	static void _register_methods();
	void _init(); //Needed by godot

	/**
	 * Initilisation of the class and the scene.
	 */
	void _ready();

private:

	/* TESTS */

	/**
	 * Initialise the player for testing
	 */
	void playerTestInit();
	void runAllTests();
	void changeDirectionTest();
};