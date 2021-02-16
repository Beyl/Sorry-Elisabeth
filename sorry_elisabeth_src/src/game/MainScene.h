#pragma once

#include <Input.hpp>
#include <GlobalConstants.hpp>

#include "Room.h"
#include "Camera.h"
#include "InventoryButton.h"

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
	 *		Manage player's movement, room and inventory interactions
	 */
	void _physics_process(); 


	/* SIGNALS */
	void on_room1_door_opened();
	void on_room_interaction_just_played();
	void on_room_interaction_finished();

	// Prevent the player from moving
	void on_mouse_entered_button();
	void on_mouse_exited_button();


	/* CONSTANTS */
	static const int PLAYER_START_X = 40;
	static const int PLAYER_START_Y = 140;
	const godot::String TAKE_HANDBAG_INTERACTION_NODE_NAME = "TakeHandbagInteraction";
	const godot::String TAKE_INTERACTION_NODE_NAME = "TakeInteraction";
	const godot::String USE_INTERACTION_NODE_NAME = "UseInteraction";
	const godot::String COMBINE_INTERACTION_NODE_NAME = "CombineInteraction";
	const godot::String OPEN_DOOR_INTERACTION_NODE_NAME = "OpenDoorInteraction";
	const godot::String ACTIVE_LIGHT_R1_INTERACTION_NODE_NAME = "ActiveLightInteractionR1";
	const godot::String ACTIVE_LIGHT_R2_INTERACTION_NODE_NAME = "ActiveLightInteractionR2";
	const godot::String INTERACT_BUTTON_NODE_NAME = "InteractButton";
	const godot::String INVENTORY_BUTTON_NODE_NAME = "InventoryButton";

private:

	// Send the player's informations to the camera
	void sendPlayerInfoToCam();

	// Recursive method that sends the inventory's, player's and room's	pointer to the interaction wich need them
	void sendInfoToInteractions(Node* currentNode);

	// Recursive method that connect the signals mouse_entered and mouse_exited from the selected nodes
	void connectButtonSignals(Node* currentNode);

	// Determine if the player can moove
	bool canPlayerMoove() const;


	/* MEMBER VARIABLES */
	// Child nodes
	Player* m_player;
	Camera* m_camera;
	Inventory* m_inventory;
	Room* m_room1;
	Room* m_room2;

	bool m_playerIsInteracting;
	bool m_mouseIsInButton;
	const godot::Input* m_inputManager;	// To manage inputs
};