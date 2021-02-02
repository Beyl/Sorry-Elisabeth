#pragma once

#include <Godot.hpp>
#include <HBoxContainer.hpp>

#include "Cell.h"
#include "../utils/Utils.h"

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


	/* CONSTANTS */
	const real_t ANIMATION_DURATION = real_t(0.5);
	static const int MAX_ITEM_NUMBER = 15;

private:

	// Update the inventory by adding and/or removing the items contained in the scene, depending on the items's array
	void updateInventory();


	/* MEMBER VARIABLES */
	// Singleton
	static Inventory* m_instance;

	// Children nodes
	godot::HBoxContainer* m_topInventory;
	godot::HBoxContainer* m_bottomInventory;
	godot::Tween* m_tween;

	Item* m_items[Inventory::MAX_ITEM_NUMBER];
	int m_itemsNumber;
	int m_currentInventorySize;
	bool m_hasGrown;

	godot::Vector2 m_hidePosition;
	godot::Vector2 m_displayPosition;
};