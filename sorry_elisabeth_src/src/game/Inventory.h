#pragma once

#include <HBoxContainer.hpp>

#include "Cell.h"
#include "UseInteraction.h"
#include "CombineInteraction.h"

class UseInteraction;
class CombineInteraction;

/**
 * Represents the player's inventory. Contain 5 to 15 cells.
 * @version 0.0
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

	void manageInteractions();

	// Put the inventory in combine or use mode. Now if cell is clicked, it manages a combine or use interaction
	void enableSpecialMode(Interaction* specialInteraction);

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
	// Execute the "combine" or "use" method depending on the inventory mode 
	void on_cellsButtonInSpecialMode_clicked(Cell* itemsCellToInteract);

	// If the inventory is in a special mode, disable it
	void on_hideAnimation_completed();

	void on_interaction_just_played();
	void on_interaction_finished();


	/* CONSTANTS */
	const real_t ANIMATION_DURATION = real_t(0.5);
	static const int MAX_ITEM_NUMBER = 15;
	static const int MIN_ITEM_NUMBER = 5;
	static const int INVENTORY_HEIGHT = 60;
	static const int INVENTORY_WIDTH = 236;

private:

	Cell* getCellWithNumber(const int cellNumber) const;

	// Search for an item wich has the name given in parameter and remove it. Do nothing if the name corresponds to nothing.
	void removeItemByName(const godot::String itemName);

	// Update the inventory by adding and/or removing the items contained in the scene, depending on the items's array
	void updateInventory();

	bool canInteract(Item* item);

	/* Disable the use of the cell's interaction table and connect their click signal to the
		"on_cellsButtonInSpecialMode_clicked" method */
	void setCellsInSpecialMode();

	// If the interactive object is able to interact with the item chosen, increase its state, otherwise play failed examintation
	void use(Cell* itemsCellToUse);

	// If the two items chosen are able to combine with each other, create a new item, otherwise play failed examination
	void combine(Cell* itemsCellToCombine);

	// Return to the initial inventory mode. We can interact normaly with the item in it.
	void disableSpecialMode();


	/* MEMBER VARIABLES */
	// Children nodes
	godot::HBoxContainer* m_topInventory;
	godot::HBoxContainer* m_bottomInventory;
	godot::Tween* m_tween;

	Item* m_items[Inventory::MAX_ITEM_NUMBER];
	int m_itemsNumber;
	int m_currentInventorySize;
	bool m_hasGrown;

	int m_specialMode;	// Equal to 0 : normal mode | Equal to 1 : use mode | Equal to 2 : combine mode
	UseInteraction* m_useInteraction;
	CombineInteraction* m_combineInteraction;
	bool m_isInteracting;

	godot::Vector2 m_hidePosition;
	godot::Vector2 m_displayPosition;
};