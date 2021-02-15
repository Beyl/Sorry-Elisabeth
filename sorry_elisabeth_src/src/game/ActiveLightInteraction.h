#pragma once

#include "Room.h"
#include "ExamineInteraction.h"

/**
 * Represents a unique interaction in the game, when the player takes up the handbag.
		It makes the inventory grow up, and change the player's sprite animation.
 */
class ActiveLightInteraction : public ExamineInteraction {

	GODOT_SUBCLASS(ActiveLightInteraction, ExamineInteraction);	// Needed by godot to be able to use this class

public:

	ActiveLightInteraction();
	~ActiveLightInteraction();

	// Register all methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	// Grow up the inventory, change player's sprite animations, remove the handbag and play the examine interaction going with it
	virtual void play();


	/* MUTATORS */
	void setRoom(Room* newRoom);


	/* PROPERTIES */
	void setSpecialSound(const godot::Ref<godot::AudioStreamSample> newSound);
	godot::Ref<godot::AudioStreamSample> getSpecialSound() const;

	void setNextInteractions(const godot::Array newInteractions);
	godot::Array getNextInteractions() const;

private:

	// Children nodes
	godot::AudioStreamPlayer* m_specialSoundPlayer;

	Room* m_room;

	// Properties
	godot::Ref<godot::AudioStreamSample> m_specialSound;
	godot::Array m_nextInteractions{};
};