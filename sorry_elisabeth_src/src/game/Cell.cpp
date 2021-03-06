#include "Cell.h"

using namespace godot;

void Cell::_register_methods()
{
	register_method("_ready", &Cell::_ready);
	register_method("_process", &Cell::_process);
	register_method("on_button_up", &Cell::on_button_up);

	register_signal<Cell>("clicked", "cell", GODOT_VARIANT_TYPE_OBJECT);
}

void Cell::_ready()
{
	connect("button_up", this, "on_button_up");
	m_isInSpecialMode = false;
	m_isDisabled = false;
	disableInteractions();

	setItem(nullptr);	// At the beginning, the cell does not contain any item
}

void Cell::_process(float delta)
{
	if (m_item != nullptr && !m_isInSpecialMode) {	// Manage user's inputs only if there is an item inside the cell

		const Vector2 mousePosition = get_global_mouse_position();

		if (Utils::isInsideArea(mousePosition, get_global_position(), get_size())) {
			if (m_itemInteractButton->isHided() && m_itemInteractionTable->isHided())
				m_item->displayInteractButton();
		}
		else {
			const Vector2 cellMarginPosition =
				Vector2(get_global_position().x - HIDE_INTERACT_BUTTON_MARGIN_X, get_global_position().y - HIDE_INTERACT_BUTTON_MARGIN_Y);
			const Vector2 cellMarginSize = Vector2(get_size().x + 2 * HIDE_INTERACT_BUTTON_MARGIN_X, get_size().y + HIDE_INTERACT_BUTTON_MARGIN_Y);

			if (!Utils::isInsideArea(mousePosition, cellMarginPosition, cellMarginSize)) {
				if (m_itemInteractButton->isDisplayed())
					m_itemInteractButton->hide();

				if (!Utils::isInsideArea(mousePosition, m_itemInteractionTable->get_global_position(), m_itemInteractionTable->get_size())) {
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
	else {
		if (!m_isInSpecialMode)
			set_disabled(true);

		if (m_item != nullptr)
			m_item->hideAll();
	}

}

void Cell::setItem(Item* newItem)
{
	if (m_item != nullptr)
		m_item->queue_free();	// Remove the ex item if there was one

	m_item = newItem;

	if (newItem != nullptr) {
		add_child(m_item);

		m_itemInteractButton = m_item->getInteractButton();
		m_itemInteractionTable = m_item->getInteractionTable();

		m_item->set_position(get_size() / 2);	// Set the item position in the middle of the cell

		m_item->connect("interaction_just_played", get_node(INVENTORY_LOCAL_PATH), "on_interaction_just_played");
		m_item->connect("interaction_finished", get_node(INVENTORY_LOCAL_PATH), "on_interaction_finished");
	}
}

Item* Cell::getItem() const
{
	return m_item;
}

bool Cell::containItem() const
{
	return m_item != nullptr;
}

void Cell::enableInteractions()
{
	m_isDisabled = false;

	set_process(true);
	set_disabled(false);
}

void Cell::disableInteractions()
{
	m_isDisabled = true;

	if (!m_isInSpecialMode) {
		set_disabled(true);
		set_process(false);
	}

	if (m_item != nullptr)
		m_item->hideAll();
}

void Cell::enableSpecialMode()
{
	m_isInSpecialMode = true;
	m_itemInteractButton->set_visible(false);
	m_itemInteractionTable->set_visible(false);
	disableInteractions();
}

void Cell::disableSpecialMode()
{
	m_isInSpecialMode = false;
	m_itemInteractButton->set_visible(true);
	m_itemInteractionTable->set_visible(true);
	enableInteractions();
}

bool Cell::isDisabled() const
{
	return m_isDisabled;
}

void Cell::on_button_up()
{
	emit_signal("clicked", this);
}

Cell::Cell()
{
	m_item = nullptr;
	m_itemInteractButton = nullptr;
	m_itemInteractionTable = nullptr;

	m_isInSpecialMode = false;
	m_isDisabled = false;
}

Cell::~Cell()
{
	if (m_item != nullptr)
		m_item->queue_free();	// normaly it is done by godot, but try to improve memory managment with the inventory
}

void Cell::_init()
{
}