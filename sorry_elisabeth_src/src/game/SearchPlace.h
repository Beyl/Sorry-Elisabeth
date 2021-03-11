#pragma once

#include "Panel.h"

/**
 * Represents the content of an open interaction. Contain or not a list of inventory items
 * @version 0.0
 */
class SearchPlace : public Panel {

	GODOT_SUBCLASS(SearchPlace, Panel);	// Needed by godot to be able to use this class

public:

	SearchPlace();
	~SearchPlace();

	void _init(); // Needed by godot

	// Enable the item's interactions
	void setIsOpen(const bool isOpen);


	/* ACCESSORS */
	godot::TextureButton* getCloseButton() const;


	/* CONSTANTS */
	const godot::String ITEM_NODE_NAME = "Item";
};