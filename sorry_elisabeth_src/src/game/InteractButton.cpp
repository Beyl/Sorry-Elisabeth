#include "InteractButton.h"

using namespace godot;

void InteractButton::_register_methods()
{
	register_method("_ready", &InteractButton::_ready);

	register_property<InteractButton, Vector2>("Hide position", &InteractButton::setHidePosition,
		&InteractButton::getHidePosition, Vector2());
	register_property<InteractButton, Vector2>("Display position", &InteractButton::setDisplayPosition,
		&InteractButton::getDisplayPosition, Vector2());
	register_property<InteractButton, real_t>("Animation duration", &InteractButton::setAnimationDuration,
		&InteractButton::getAnimationDuation, real_t(0.2));
}

void InteractButton::_ready()
{
	// Get children
	m_tween = get_node("Tween")->cast_to<Tween>(get_node("Tween"));
	m_animationPlayer = get_node("AnimationPlayer")->cast_to<AnimationPlayer>(get_node("AnimationPlayer"));

	// Scene initialisation
	set_modulate(NO_OPACITY);
	set_draw_behind_parent(true);
	set_pivot_offset(get_size() / 2);
	set_scale(INVERT_SCALE);
}

void InteractButton::display()
{
	m_tween->interpolate_property(this, "rect_position", m_hidePosition, m_displayPosition, m_animationDuration,
		Tween::TRANS_BOUNCE, Tween::EASE_OUT);
	m_tween->start();

	m_tween->interpolate_property(this, "modulate", NO_OPACITY, FULL_OPACITY, m_animationDuration,
		Tween::TRANS_LINEAR, Tween::EASE_IN);
	m_tween->start();

	m_animationPlayer->play("turn_around");
}

void InteractButton::hide()
{
	m_tween->interpolate_property(this, "rect_position", m_displayPosition, m_hidePosition, m_animationDuration,
		Tween::TRANS_LINEAR, Tween::EASE_OUT);
	m_tween->start();

	m_tween->interpolate_property(this, "modulate", FULL_OPACITY, NO_OPACITY, m_animationDuration,
		Tween::TRANS_LINEAR, Tween::EASE_OUT);
	m_tween->start();

	m_animationPlayer->play_backwards("turn_around");
}

bool InteractButton::isDisplayed()
{
	return get_modulate() == FULL_OPACITY;
}

void InteractButton::setHidePosition(godot::Vector2 newPosition)
{
	m_hidePosition = newPosition;
}

godot::Vector2 InteractButton::getHidePosition()
{
	return m_hidePosition;
}

void InteractButton::setDisplayPosition(godot::Vector2 newPosition)
{
	m_displayPosition = newPosition;
}

godot::Vector2 InteractButton::getDisplayPosition()
{
	return m_displayPosition;
}

void InteractButton::setAnimationDuration(real_t newDuration)
{
	if (newDuration <= MIN_ANIMATION_DURATION)
		m_animationDuration = MIN_ANIMATION_DURATION;
	else
		m_animationDuration = newDuration;
}

real_t InteractButton::getAnimationDuation()
{
	return m_animationDuration;
}

InteractButton::InteractButton()
{
	m_tween = 0;
	m_animationPlayer = 0;
	m_hidePosition = Vector2();
	m_displayPosition = Vector2();
	m_animationDuration = 0;
;}

InteractButton::~InteractButton()
{
}

void InteractButton::_init()
{
}