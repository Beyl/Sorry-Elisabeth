#include "InventoryButton.h"

using namespace godot;

void InventoryButton::_register_methods()
{
	register_method("_ready", &InventoryButton::_ready);
	register_method("_process", &InventoryButton::_process);
	register_method("on_button_released", &InventoryButton::on_button_released);
	register_method("on_Inventory_interact", &InventoryButton::on_Inventory_interact);
}

void InventoryButton::_ready()
{
	// Get children
	m_fadeBackground = get_node("FadeBackground")->cast_to<FadeBackground>(get_node("FadeBackground"));
	m_inventory = get_node("Inventory")->cast_to<Inventory>(get_node("Inventory"));
	m_animationPlayer = get_node("AnimationPlayer")->cast_to<AnimationPlayer>(get_node("AnimationPlayer"));

	// Signal initialisation
	connect("button_up", this, "on_button_released");
	m_inventory->connect("interact", this, "on_Inventory_interact");
}

void InventoryButton::_process(float delta)
{
	if (m_fadeBackground->isDisplayed()) {
		Vector2 mousePosition = get_global_mouse_position();

		if (Utils::isInsideObject(mousePosition, get_global_position(), get_size()))
			m_fadeBackground->set_mouse_filter(Control::MOUSE_FILTER_IGNORE);
		else
			m_fadeBackground->set_mouse_filter(Control::MOUSE_FILTER_STOP);
	}
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
	m_fadeBackground->set_mouse_filter(Control::MOUSE_FILTER_STOP);
}

void InventoryButton::hideAll()
{
	m_inventory->hide();
	m_fadeBackground->fadeOut();
	m_fadeBackground->set_mouse_filter(Control::MOUSE_FILTER_IGNORE);
}

InventoryButton::InventoryButton()
{
	m_fadeBackground = nullptr;
	m_inventory = nullptr;
	m_animationPlayer = nullptr;
}

InventoryButton::~InventoryButton()
{
}

void InventoryButton::_init()
{
}