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
 * Gather the player, the camera, the rooms and the GUI to connect them
 */
class MainScene : public godot::Node2D {

	GODOT_CLASS(MainScene, godot::Node2D);	//To make godot able to use this class

public:

	MainScene();
	~MainScene();

	/**
	 * Register the methods and properties godot is directly going to call and use
	 */
	static void _register_methods();
	void _init();	//Needed by godot

	/**
	 * Initilisation of the class and the scene
	 */
	void _ready();

	/**
	 * Called every tic (60 times per secondes)
	 *		Manage user's inputs
	 */
	void _physics_process();

private:

	/**
	 * Send the player's informations to the camera
	 */
	void sendPlayerInfoToCam();



	/* MEMBER VARIABLES */

	//Child nodes
	Player* m_player;
	Camera* m_camera;

	bool m_gameSceneActive;

	godot::Input* m_inputManager;	//To manage inputs



	/* CONSTANTS */

	static const int PLAYER_START_X = 25;
	static const int PLAYER_START_Y = 100;
};