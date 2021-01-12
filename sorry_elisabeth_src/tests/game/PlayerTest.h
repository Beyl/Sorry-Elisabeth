#include "../pch.h"

#include <Godot.hpp>
#include <Node2D.hpp>

#include "../../src/game/Player.h"

/**
 * Test the Player class's methods using godot and gtest
 */
class PlayerTest : public godot::Node2D {

	GODOT_CLASS(PlayerTest, godot::Node2D);

public:
	/* CONSTRUCTOR & DESTRUCTOR */

	/**
	 * Constructor, usefull only to create an instance and avoid warnings,
	 *		the initialisation is done in the "_ready" method.
	 */
	PlayerTest();

	/**
	 * Destructor, usefull only to create the class and avoid warnings,
	 *		godot deallocates the memory itself.
	 */
	~PlayerTest();

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
	 * Initialise the player for testing
	 */
	void playerTestInit();

	/**
	 * Run all the tests methods
	 */
	void runAllTests();

	/**
	 * "changeDirection" method tests
	 */
	void changeDirectionTest();

	Player* m_player;
};