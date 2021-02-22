#pragma once

#include "ExamineInteraction.h"
#include "InventoryButton.h"

class Inventory;

/**
 * Offers the possibility to use an item coming from the inventory over an interactive object
 */
class UseInteraction : public ExamineInteraction {

	GODOT_SUBCLASS(UseInteraction, ExamineInteraction);	// Needed by godot to be able to use this class

public:

	UseInteraction();
	~UseInteraction();

	// Register the methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	// Needed by godot

	// Add the item to the inventory and remove the parent interactive object
	virtual void play();

	void playFailedExamination();
	void playSucceededExamination();


	/* MUTATORS */
	void setInventory(Inventory* newInventory);


	/* PROPERTIES */
	void setNextInteractions(const godot::Array newInteractions);
	godot::Array getNextInteractions() const;

	void setUseFailedExaminationText(const godot::String newText);
	godot::String getUseFailedExaminationText() const;

	void setUseFailedSound(const godot::Ref<godot::AudioStreamSample> newSound);
	godot::Ref<godot::AudioStreamSample> getUseFailedSound() const;

private:

	Inventory* m_inventory;

	// Properties
	godot::Array m_nextInteractions;
	godot::String m_useFailedText;
	godot::Ref<godot::AudioStreamSample> m_failedSound;
};