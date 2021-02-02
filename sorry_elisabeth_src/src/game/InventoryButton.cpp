#include "InventoryButton.h"

using namespace godot;

void InventoryButton::_register_methods()
{
	register_method("_ready", &InventoryButton::_ready);
	register_method("on_button_released", &InventoryButton::on_button_released);
}

void InventoryButton::_ready()
{
	// Get children
	m_fadeBackground = get_node("FadeBackground")->cast_to<FadeBackground>(get_node("FadeBackground"));
	m_inventory = get_node("Inventory")->cast_to<Inventory>(get_node("Inventory"));

	// Scene intialisation
	m_fadeBackground->set_global_position(Vector2(0, 0));
	m_fadeBackground->set_size(Vector2(Utils::SCREEN_WIDTH, Utils::SCREEN_HEIGHT));

	connect("button_up", this, "on_button_released");

	Item* item2 = get_node("Item2")->cast_to<Item>(get_node("Item2"));
	Item* item = get_node("Item")->cast_to<Item>(get_node("Item"));

	m_inventory->addItem(item2);
	m_inventory->addItem(item);
	m_inventory->removeItem(get_node("Inventory/TopBox/Cell0")->cast_to<Cell>(get_node("Inventory/TopBox/Cell0"))->getItem());
}

void InventoryButton::on_button_released()
{
	if (m_fadeBackground->isDisplayed())
		hideAll();
	else {
		if (m_fadeBackground->isHided())
			displayAll();
	}
}

void InventoryButton::displayAll()
{
	m_inventory->display();
	m_fadeBackground->fadeIn();
}

void InventoryButton::hideAll()
{
	m_inventory->hide();
	m_fadeBackground->fadeOut();
}

InventoryButton::InventoryButton()
{
	m_fadeBackground = 0;
	m_inventory = 0;
}

InventoryButton::~InventoryButton()
{
}

void InventoryButton::_init()
{
}