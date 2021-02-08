#pragma once

#include <HBoxContainer.hpp>

#include "Cell.h"
#include "UseInteraction.h"

class UseInteraction;

/**
 * Represents the player's inventory.
		Contain 15 cells to keep and interact with diferent items.
 */
class Inventory : public godot::Container {

	GODOT_CLASS(Inventory, godot::Container);	// Needed by godot to be able to use this class

public:

	Inventory();
	~Inventory();

	// Register all the methods and properties that godot is directly going to use and call
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	void display();
	void hide();

	void addItem(Item* newItem);
	void removeItem(const Item* itemToDelete);

	// When a cell is clicked, if the item in it is able to interact with objectToInteract, increase it's state
	void enableUseMode(UseInteraction* useInteraction);

	// Display the bottom part of the inventory and offer 10 more places
	void grow();
	
	/**
	 * Search the value given in parameter in the array of Item's pointers.
	 *
	 * @param itemArray, the array of Item's pointers
	 * @param arraySize, the size of the array
	 * @param pointer, the value to search
	 * @return the index of the first pointer equal to the value found in the array or -1 if it's not present
	 */
	static int searchItemInArray(Item* itemsArray[], const int arraySize, const Item* pointer);

	/**
	 * Remove the element at the index gave in parameter, and shift the rest of the elements to the left
	 *
	 * @param itemArray, the array of Item's pointers
	 * @param arraySize, the size of the array
	 * @param idItem, the id of the element to remove
	 */
	static void removeItemInArray(Item* itemsArray[], const int arraySize, const int idItem);


	/* SIGNALS */
	// Check if the cell's item 
	void on_cellsButtonInUseMode_clicked(Cell* itemsCellToUse);

	// If the inventory is in use mode, disable it
	void on_hideAnimation_completed();

	/* CONSTANTS */
	const real_t ANIMATION_DURATION = real_t(0.5);
	static const int MAX_ITEM_NUMBER = 15;
	static const int MIN_ITEM_NUMBER = 5;

private:

	// Update the inventory by adding and/or removing the items contained in the scene, depending on the items's array
	void updateInventory();

	// Disable the use of the cell's interaction table and connect their click signal to the "" method
	void setCellsInUseMode();

	// Return to the initial inventory mode
	void disableUseMode();


	/* MEMBER VARIABLES */
	// Children nodes
	godot::HBoxContainer* m_topInventory;
	godot::HBoxContainer* m_bottomInventory;
	godot::Tween* m_tween;

	Item* m_items[Inventory::MAX_ITEM_NUMBER];
	int m_itemsNumber;
	int m_currentInventorySize;
	bool m_hasGrown;

	bool m_isInUseMode;
	UseInteraction* m_useInteraction;

	godot::Vector2 m_hidePosition;
	godot::Vector2 m_displayPosition;
};