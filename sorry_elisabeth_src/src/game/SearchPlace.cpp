#include "SearchPlace.h"
#include "Item.h"

using namespace godot;

void SearchPlace::setIsOpen(const bool isOpen)
{
	for (int i = 0; i < get_child_count(); i++) {
		if (get_child(i)->get_name().find(ITEM_NODE_NAME) != -1) {
			if (isOpen)
				get_child(i)->cast_to<Item>(get_child(i))->enableOpenMode();
			else
				get_child(i)->cast_to<Item>(get_child(i))->disableOpenMode();
		}
	}
}

godot::TextureButton* SearchPlace::getCloseButton() const
{
	return m_closeButton;
}

SearchPlace::SearchPlace()
{
}

SearchPlace::~SearchPlace()
{
}

void SearchPlace::_init()
{
}