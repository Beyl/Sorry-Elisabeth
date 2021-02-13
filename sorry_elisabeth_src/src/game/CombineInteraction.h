#pragma once

#include "ExamineInteraction.h"
#include "Inventory.h"

class Inventory;

/**
 * Offers the possiblity to combine two items together to create a new one.
 */
class CombineInteraction : public ExamineInteraction {

	GODOT_SUBCLASS(CombineInteraction, ExamineInteraction);	// Needed by godot to be able to use this class

public:

	CombineInteraction();
	~CombineInteraction();

	// Register the methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	// Needed by godot

	// Set the inventory to combine mode, and let the player choose an item to combine with
	virtual void play();

	void playFailedExamination();
	void playSucceededExamination();


	/* MUTATORS */
	void setInventory(Inventory* newInventory);


	/* PROPERTIES */
	void setCombinedItems(const godot::Dictionary newCombinedItems);
	godot::Dictionary getCombinedItems() const;

	void setCombineFailedExaminationText(const godot::String newText);
	godot::String getCombineFailedExaminationText() const;

	void setCombineFailedSound(const godot::Ref<godot::AudioStreamSample> newSound);
	godot::Ref<godot::AudioStreamSample> getCombineFailedSound() const;

private:

	Inventory* m_inventory;

	// Properties
	godot::Dictionary m_combinedItems;
	godot::String m_combineFailedText;
	godot::Ref<godot::AudioStreamSample> m_failedSound;
};