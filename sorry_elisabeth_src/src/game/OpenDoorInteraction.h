#pragma once

#include "Room.h"
#include "SpecialInteraction.h"

/**
 * Represents a unique interaction in the game, when the player open the door between the rooms.
 * @version 0.0
 */
class OpenDoorInteraction : public ExamineInteraction {

	GODOT_SUBCLASS(OpenDoorInteraction, ExamineInteraction);	// Needed by godot to be able to use this class

public:

	OpenDoorInteraction();
	~OpenDoorInteraction();

	// Register all methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	// Grow up the inventory, change player's sprite animations, remove the handbag and play the examine interaction going with it
	virtual void play();


	/* MUTATORS */
	void setRoom(Room* newRoom);

	
	/* SIGNALS */
	// Play the sound and increase it's parent interactive object state (next animation + next interactions)
	void on_fadeIn_finished();

	// Start fading out
	void on_specialSound_played();

	// Play the examine interaction associated with the special interaction
	void on_fadeOut_finished();


	/* PROPERTIES */
	void setSpecialSound(const godot::Ref<godot::AudioStreamSample> newSound);
	godot::Ref<godot::AudioStreamSample> getSpecialSound() const;

	void setNextInteractions(const godot::Array newInteractions);
	godot::Array getNextInteractions() const;

private:

	// Children nodes
	FadeBackground* m_fadeBackground;
	godot::AudioStreamPlayer* m_specialSoundPlayer;

	Room* m_room;

	// Properties
	godot::Ref<godot::AudioStreamSample> m_specialSound;
	godot::Array m_nextInteractions{};
};