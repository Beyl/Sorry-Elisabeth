#include "InventoryButton.h"

using namespace godot;

void InventoryButton::_register_methods()
{
	register_method("_ready", &InventoryButton::_ready);
	register_method("on_button_released", &InventoryButton::on_button_released);
	register_method("on_Inventory_interact", &InventoryButton::on_Inventory_interact);
}

void InventoryButton::_ready()
{
	// Get children
	m_fadeBackground = get_node("FadeBackground")->cast_to<FadeBackground>(get_node("FadeBackground"));
	m_inventory = get_node("Inventory")->cast_to<Inventory>(get_node("Inventory"));
	m_animationPlayer = get_node("AnimationPlayer")->cast_to<AnimationPlayer>(get_node("AnimationPlayer"));

	// Scene intialisation
	m_fadeBackground->set_global_position(Vector2(0, 0));
	m_fadeBackground->set_size(Vector2(Utils::SCREEN_WIDTH, Utils::SCREEN_HEIGHT));

	// Signal initialisation
	connect("button_up", this, "on_button_released");
	m_inventory->connect("interact", this, "on_Inventory_interact");
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

void InventoryButton::on_Inventory_interact()
{
	m_animationPlayer->play("interactionSignal");
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
	m_animationPlayer = 0;
}

InventoryButton::~InventoryButton()
{
}

void InventoryButton::_init()
{
}