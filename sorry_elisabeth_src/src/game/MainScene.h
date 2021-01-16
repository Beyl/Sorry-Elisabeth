#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <Input.hpp>
#include <GlobalConstants.hpp>

#include "../utils/Utils.h"
#include "Player.h"
#include "Camera.h"

/**
 * Represent the main scene in the game
 * 
 * Gather the player, the camera, the rooms and the GUI and connect them
 */
class MainScene : public godot::Node2D {

	//To make godot able to use this class
	GODOT_CLASS(MainScene, godot::Node2D);

public:
	/* CONSTRUCTOR && DESTRUCTOR */

	/**
	 * Constructor, usefull only to create the class and avoid warnings,
	 *		the real initialisation is done in the "_ready" method.
	 */
	MainScene();

	/**
	 * Destructor, usefull only to create the class and avoid warnings,
	 *		godot deallocates the memory itself.
	 */
	~MainScene();

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
	 * Initilisation of the class and the scene here.
	 *		Called after the parent node and all its children entenred a scene.
	 */
	void _ready();

	/**
	 * Called every tic (60 times per secondes).
	 */
	void _physics_process();

	/**
	 * Send the player's informations to the camera
	 */
	void sendPlayerInfoToCam();

private:
	//Child nodes
	Player* m_player;
	Camera* m_camera;

	bool m_gameSceneActive;

	godot::Input* m_inputManager;	//To interact with inputs
};