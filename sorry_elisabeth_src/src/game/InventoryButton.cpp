#include "InventoryButton.h"

using namespace godot;

void InventoryButton::_register_methods()
{
	register_method("_ready", &InventoryButton::_ready);
	register_method("_process", &InventoryButton::_process);
	register_method("on_button_released", &InventoryButton::on_button_released);
	register_method("on_Inventory_interact", &InventoryButton::on_Inventory_interact);
	register_method("on_tween_all_completed", &InventoryButton::on_tween_all_completed);

	register_property<InventoryButton, Vector2>("Display position", &InventoryButton::setDisplayPosition,
		&InventoryButton::getDisplayPosition, Vector2());
	register_property<InventoryButton, Vector2>("Hide position", &InventoryButton::setHidePosition,
		&InventoryButton::getHidePosition, Vector2());
}

void InventoryButton::_ready()
{
	// Get children
	m_fadeBackground = get_node("FadeBackground")->cast_to<FadeBackground>(get_node("FadeBackground"));
	m_inventory = get_node("Inventory")->cast_to<Inventory>(get_node("Inventory"));
	m_animationPlayer = get_node("AnimationPlayer")->cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	m_tween = get_node("Tween")->cast_to<Tween>(get_node("Tween"));

	// Scene initialisation
	m_isAnimated = false;
	m_isDisplaying = false;

	// Signal initialisation
	connect("button_up", this, "on_button_released");
	m_inventory->connect("interact", this, "on_Inventory_interact");
	m_tween->connect("tween_all_completed", this, "on_tween_all_completed");
}

void InventoryButton::_process(float delta)
{
	if (m_fadeBackground->isDisplayed()) {
		Vector2 mousePosition = get_global_mouse_position();

		if (Utils::isInsideObject(mousePosition, get_global_position(), get_size()))
			m_fadeBackground->set_mouse_filter(Control::MOUSE_FILTER_IGNORE);
		else
			m_fadeBackground->set_mouse_filter(Control::MOUSE_FILTER_STOP);

		if (m_isAnimated)
			m_inventory->set_global_position(INVENTORY_GLOBAL_POSITION);
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

void InventoryButton::hideButton()
{
	if (get_position() == m_displayPosition) {
		m_tween->interpolate_property(this, "rect_position", m_displayPosition, m_hidePosition,
			real_t(TWEEN_ANIMATION_DURATION / 1.5), Tween::TRANS_BACK, Tween::EASE_IN_OUT);
		m_tween->start();

		m_isAnimated = true;
	}
}

void InventoryButton::displayButton()
{
	if (get_position() == m_hidePosition) {
		m_tween->interpolate_property(this, "rect_position", m_hidePosition, m_displayPosition, TWEEN_ANIMATION_DURATION,
			Tween::TRANS_BOUNCE, Tween::EASE_OUT);
		m_tween->start();

		m_isAnimated = true;
	}
}

bool InventoryButton::isInventoryOpen() const
{
	return m_fadeBackground->isDisplayed();
}

void InventoryButton::on_tween_all_completed()
{
	m_isAnimated = false;
}

void InventoryButton::setDisplayPosition(const godot::Vector2 position)
{
	m_displayPosition = position;
}

godot::Vector2 InventoryButton::getDisplayPosition() const
{
	return m_displayPosition;
}

void InventoryButton::setHidePosition(const godot::Vector2 position)
{
	m_hidePosition = position;
}

godot::Vector2 InventoryButton::getHidePosition() const
{
	return m_hidePosition;
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
	m_tween = nullptr;

	m_displayPosition = Vector2();
	m_hidePosition = Vector2();
	m_isAnimated = false;
	m_isDisplaying = false;
}

InventoryButton::~InventoryButton()
{
}

void InventoryButton::_init()
{
}