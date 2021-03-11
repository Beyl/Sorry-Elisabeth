#include "Panel.h"

using namespace godot;

void Panel::_register_methods()
{
	register_method("_ready", &Panel::_ready);
	register_method("on_closeButton_released", &Panel::on_closeButton_released);
}

void Panel::_ready()
{
	// Get children
	m_tween = get_node("Tween")->cast_to<Tween>(get_node("Tween"));
	m_closeButton = get_node("CloseButton")->cast_to<TextureButton>(get_node("CloseButton"));

	// Scene intialisation

	// Set hiding and display position
	const Vector2 searchPlaceSize = get_rect().get_size();
	m_displayPosition = Utils::getCenteredPosition(searchPlaceSize);
	m_hidingPosition = Vector2(m_displayPosition.x,
		m_displayPosition.y + Utils::SCREEN_HEIGHT / 2 + searchPlaceSize.y / 2 + m_closeButton->get_size().y / 2);

	set_position(m_hidingPosition);	// Entering a scene, a search place is always hided

	// Signals initialisation
	m_closeButton->connect("button_up", this, "on_closeButton_released");
	add_user_signal("just_closed");
}

void Panel::display()
{
	// Interpolate the panel's position from its hiding position to his display position
	m_tween->interpolate_property(this, "rect_position", m_hidingPosition, m_displayPosition,
		ANIMATION_DURATION, Tween::TRANS_BACK, Tween::EASE_OUT);
	m_tween->start();
}

void Panel::hide()
{
	// Interpolate the panel's position from its display position to his hiding position
	m_tween->interpolate_property(this, "rect_position", m_displayPosition, m_hidingPosition,
		ANIMATION_DURATION, Tween::TRANS_BACK, Tween::EASE_IN);
	m_tween->start();

	emit_signal("just_closed");
}

bool Panel::isHided() const
{
	return get_position() == m_hidingPosition;
}

void Panel::on_closeButton_released()
{
	hide();
}

real_t Panel::getAnimationDuration() const
{
	return ANIMATION_DURATION;
}

Panel::Panel()
{
	m_tween = nullptr;
	m_closeButton = nullptr;

	m_displayPosition = Vector2(0, 0);
	m_hidingPosition = Vector2(0, 0);
}

Panel::~Panel()
{
}

void Panel::_init()
{
}