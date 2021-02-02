#include "Cell.h"

using namespace godot;

void Cell::_register_methods()
{
	register_method("_ready", &Cell::_ready);
	register_method("_process", &Cell::_process);
}

void Cell::_ready()
{
	setItem(0);	// At the beginning, the cell does not contain any item
}

void Cell::_process()
{
	if (m_item != 0) {	// Manage user's inputs only if there is an item inside the cell

		const Vector2 mousePosition = get_global_mouse_position();

		if (Utils::isInsideObject(mousePosition, get_global_position(), get_size())) {
			if (m_itemInteractButton->isHided() && m_itemInteractionTable->isHided())
				m_item->displayInteractButton();
		}
		else {
			const Vector2 cellMarginPosition =
				Vector2(get_global_position().x - HIDE_INTERACT_BUTTON_MARGIN_X, get_global_position().y - HIDE_INTERACT_BUTTON_MARGIN_Y);
			const Vector2 cellMarginSize = Vector2(get_size().x + 2 * HIDE_INTERACT_BUTTON_MARGIN_X, get_size().y + HIDE_INTERACT_BUTTON_MARGIN_Y);

			if (!Utils::isInsideObject(mousePosition, cellMarginPosition, cellMarginSize)) {
				if (m_itemInteractButton->isDisplayed())
					m_itemInteractButton->hide();

				if (!Utils::isInsideObject(mousePosition, m_itemInteractionTable->get_global_position(), m_itemInteractionTable->get_size())) {
					if (m_itemInteractionTable->isDisplayed())
						m_itemInteractionTable->hide();
				}
			}
		}

		if (!m_itemInteractionTable->isHided())
			set_disabled(true);
		else
			set_disabled(false);
	}
	else
		set_disabled(true);

}

void Cell::setItem(Item* newItem)
{
	if (m_item != 0)
		m_item->queue_free();	// Remove the ex item if there was one

	m_item = newItem;

	if (newItem != 0) {
		add_child(m_item);

		m_itemInteractButton = m_item->getInteractButton();
		m_itemInteractionTable = m_item->getInteractionTable();

		m_item->set_position(get_size() / 2);	// Set the item position in the middle of the cell
	}
}

Item* Cell::getItem() const
{
	return m_item;
}

bool Cell::containItem() const
{
	return m_item != 0;
}

Cell::Cell()
{
	m_item = 0;
	m_itemInteractButton = 0;
	m_itemInteractionTable = 0;
}

Cell::~Cell()
{
	if (m_item != 0)
		m_item->queue_free();
}

void Cell::_init()
{
}