#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <Input.hpp>
#include <GlobalConstants.hpp>

#include "../utils/Utils.h"
#include "Player.h"
#include "Camera.h"
#include "InventoryButton.h"
#include "TakeHangbagInteraction.h"
#include "TakeInteraction.h"

/**
 * Represent the main scene in the game.
		 Gather the player, the camera, the rooms and the GUI to connect them
 */
class MainScene : public godot::Node2D {

	GODOT_CLASS(MainScene, godot::Node2D);	// Needed by godot to be able to use this class

public:

	MainScene();
	~MainScene();

	// Register the methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	/**
	 * Called every tic (60 times per secondes)
	 *		Manage user's inputs
	 */
	void _physics_process(); 


	/* CONSTANTS */
	static const int PLAYER_START_X = 40;
	static const int PLAYER_START_Y = 117;
	const godot::String TAKE_HANDBAG_INTERACTION_NODE_NAME = "TakeHandbagInteraction";
	const godot::String TAKE_INTERACTION_NODE_NAME = "TakeInteraction";

private:

	// Send the player's informations to the camera
	void sendPlayerInfoToCam();

	// Recursive method that sends the inventory's and player's pointer to the interaction wich need them
	void sendInfoToInteractions(Node* currentNode);


	/* MEMBER VARIABLES */
	// Child nodes
	Player* m_player;
	Camera* m_camera;
	Inventory* m_inventory;

	bool m_gameSceneActive;
	const godot::Input* m_inputManager;	// To manage inputs
};