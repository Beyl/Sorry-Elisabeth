#pragma once

#include "InteractiveObject.h"
#include "Player.h"

/**
 * Represents a room which contain a background and several interactive objects and lights.
 * Gather them together to handle interctions with player.
 */
class Room : public godot::Node2D {

	GODOT_CLASS(Room, godot::Node2D); // Needed by godot to be able to use this class

public:

	Room();
	~Room();

	static void _register_methods();	// Register all methods and signals that godot is directly going to call
	void _init();	// Needed by godot

	void _ready();
	void clearAndGetInteractiveObjects();

	void manageInteractions();
	bool isPlayerInteracting() const;
	bool isPlayerInside() const;


	/* SIGNALS */
	void on_interaction_just_played();
	void on_interaction_finished();

	void on_itemOpenInteraction_just_played();
	void on_itemOpenInteraction_finished();


	/* ACCESSORS & MUTATORS */
	void setPlayer(Player* player);

	void setDoorIsOpen(const bool isOpen);
	bool getDoorIsOpen() const;

	void setInventoryIsOpen(const bool isOpen);

	void setLightIsOn(const bool setOn);
	bool isLightTurnOn() const;


	/* CONSTANTS */
	const godot::String INTERACTIVE_OBJECT_NAME_PART = "IO";
	const godot::String ITEM_NODE_NAME_PART = "Item";
	const godot::String LIGHT_NODE_NAME_PART = "Light";
	static const int ROOM_HEIGHT_BEGINNING = 0;
	static const int ROOM_HEIGHT_ENDING = 150;
	static const int ROOM_WIDTH_BEGINNING = -40;
	static const int ROOM_WIDTH_ENDING = 660;
	static const int CAN_INTERACT_RANGE = 15;

private:

	void getInteractiveObjects(godot::Node* node);
	void connectInteractionSignals(godot::Node* node);
	void getLights();

	bool isInInteractionZone(InteractiveObject* object) const;
	bool canInteract(InteractiveObject* object) const;


	/* MEMBER VARIABLES */
	godot::Array m_lights;
	godot::Array m_interactiveObjects;
	Player* m_player;

	bool m_playerIsInteracting;
	bool m_isOpenInteracting;
	bool m_isInventoryOpen;
	bool m_lightIsOn;
	bool m_doorIsOpened;
};