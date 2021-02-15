#pragma once

#include <Input.hpp>
#include <GlobalConstants.hpp>

#include "Room.h"
#include "Camera.h"
#include "InventoryButton.h"
#include "TakeHangbagInteraction.h"
#include "TakeInteraction.h"
#include "OpenDoorInteraction.h"

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


	/* SIGNALS */
	void on_room1_door_opened();


	/* CONSTANTS */
	static const int PLAYER_START_X = 40;
	static const int PLAYER_START_Y = 117;
	const godot::String TAKE_HANDBAG_INTERACTION_NODE_NAME = "TakeHandbagInteraction";
	const godot::String TAKE_INTERACTION_NODE_NAME = "TakeInteraction";
	const godot::String USE_INTERACTION_NODE_NAME = "UseInteraction";
	const godot::String COMBINE_INTERACTION_NODE_NAME = "CombineInteraction";
	const godot::String OPEN_DOOR_INTERACTION_NODE_NAME = "OpenDoorInteraction";

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
	Room* m_room1;

	bool m_gameSceneActive;
	const godot::Input* m_inputManager;	// To manage inputs
};