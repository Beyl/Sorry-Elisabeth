#pragma once

#include "InteractionTable.h"
#include "InteractButton.h"
#include "Interaction.h"

/**
 * Represents a room object wich the player will be able to interact with.
 * @version 0.0
 */
class InteractiveObject : public godot::AnimatedSprite {

	GODOT_CLASS(InteractiveObject, godot::AnimatedSprite);	// Needed by godot to be able to use this class

public:

	InteractiveObject();
	~InteractiveObject();

	// Register all the methods and properties that godot is directly going to use and call
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	void displayInteractButton();

	// Hide the interact button AND the interaction table
	void hideAll();
	
	// Determine if the interactive object is still offering interactions
	bool offerInteractions() const;

	// Set the next animation and the new interactions going with it
	void increaseState(godot::Array nextInteractions, Interaction* increaseTypeInteraction);


	/* SIGNALS */
	// Display the interaction table
	void on_interactButton_released();

	void on_interaction_table_displayed();

	// Add the new interactions to the interaction table
	void on_increaseTypeInteraction_finished();

	void on_interaction_just_played();
	void on_interaction_finished();


	/* PROPERTIES */
	void setObjectStateNumber(const int stateNumber);
	int getObjectStateNumber() const;

	void setObjectSize(const godot::Vector2 newSize);
	godot::Vector2 getObjectSize() const;

	void setUseItemName(const godot::String newItemName);
	godot::String getUseItemName() const;

	void setInteractOnlyWhenLighted(const bool canInteract);
	bool interactOnlyWhenLighted() const;

protected:

	// Calculate the table position depending on the number of interactions in it
	void setInteractionTablePosition();

	// Child nodes
	InteractButton* m_interactButton;
	InteractionTable* m_interactionTable;

	int m_state;
	godot::String m_useItemName;

	// Properties
	int m_objectStateNumber;
	godot::Vector2 m_objectSize;

private:

	bool m_interactOnlyWhenLighted;
};