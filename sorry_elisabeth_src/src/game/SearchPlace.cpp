#include "SearchPlace.h"

using namespace godot;

void SearchPlace::_register_methods()
{
	register_method("_ready", &SearchPlace::_ready);
	register_method("on_closeButton_released", &SearchPlace::on_closeButton_released);
}

void SearchPlace::_ready()
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

	// Entering a scene, a search place is always hided
	set_position(m_hidingPosition);
	m_closeButton->connect("button_up", this, "on_closeButton_released");
}

void SearchPlace::display()
{
	m_tween->interpolate_property(this, "rect_position", m_hidingPosition, m_displayPosition,
		TWEEN_ANIMATION_DURATION, Tween::TRANS_BACK, Tween::EASE_OUT);
	m_tween->start();
}

void SearchPlace::hide()
{
	m_tween->interpolate_property(this, "rect_position", m_displayPosition, m_hidingPosition,
		TWEEN_ANIMATION_DURATION, Tween::TRANS_CUBIC, Tween::EASE_OUT);
	m_tween->start();
}

void SearchPlace::on_closeButton_released()
{
	hide();
}

real_t SearchPlace::getAnimationDuration() const
{
	return TWEEN_ANIMATION_DURATION;
}

godot::TextureButton* SearchPlace::getCloseButton() const
{
	return m_closeButton;
}

SearchPlace::SearchPlace()
{
	m_tween = nullptr;
	m_closeButton = nullptr;

	m_displayPosition = Vector2(0, 0);
	m_hidingPosition = Vector2(0, 0);
}

SearchPlace::~SearchPlace()
{
}

void SearchPlace::_init()
{
}