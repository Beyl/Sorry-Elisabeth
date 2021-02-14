#pragma once

#include "InteractiveObject.h"
#include "Player.h"

class Room : public godot::Node2D {

	GODOT_CLASS(Room, godot::Node2D);

public:

	Room();
	~Room();

	static void _register_methods();
	void _init();	// Needed by godot;

	void _ready();

	void manageInteractions();

	bool isPlayerInteracting() const;
	bool isPlayerInside() const;

	void turnOnLights();
	void turnOffLights();
	bool isLightTurnOn() const;


	/* SIGNALS */
	void on_interaction_just_played();
	void on_interaction_finished();


	/* ACCESSORS & MUTATORS */
	void setPlayer(Player* player);
	void setDoorIsOpen(const bool isOpen);
	bool getDoorIsOpen() const;


	/* CONSTANTS */
	const godot::String INTERACTIVE_OBJECT_NAME_PART = "IO";

private:

	void getInteractiveObjects();
	void connectInteractionSignal();

	bool isInInteractionZone(InteractiveObject* object) const;
	bool canInteract(InteractiveObject* object) const;

	/* MEMBER VARIABLES */
	godot::Array m_interactiveObjects;
	Player* m_player;

	bool m_playerIsInteracting;
	bool m_lightIsOn;
	bool m_doorIsOpened;
};