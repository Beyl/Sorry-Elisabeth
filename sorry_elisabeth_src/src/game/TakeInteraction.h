#pragma once

#include "ExamineInteraction.h"
#include "Inventory.h"

class TakeInteraction : public ExamineInteraction {

	GODOT_SUBCLASS(TakeInteraction, ExamineInteraction);	// Needed by godot to be able to use this class

public:

	TakeInteraction();
	~TakeInteraction();

	// Register the methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	// Add the item to the inventory and remove the parent interactive object
	virtual void play();


	/* SIGNALS */
	// Remove the parent interactive object from the scene
	void on_examineInteraction_finished();


	/* MUTATORS */
	void setInventory(Inventory* newInventory);


	/* PROPERTIES */
	void setItemScene(const godot::Ref<godot::PackedScene> newItemScene);
	godot::Ref<godot::PackedScene> getItemScene() const;

	void setItemSceneName(const godot::String newName);
	godot::String getItemSceneName() const;

private:

	Inventory* m_inventory;
	InteractiveObject* m_parentInteractiveObject;

	// Properties
	godot::Ref<godot::PackedScene> m_itemScene;
	godot::String m_itemSceneName;
};