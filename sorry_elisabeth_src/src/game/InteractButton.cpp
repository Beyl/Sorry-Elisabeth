#include "InteractButton.h"

using namespace godot;

void InteractButton::_register_methods()
{
	register_method("_ready", &InteractButton::_ready);
	register_method("on_displayAnimation_finished", &InteractButton::on_displayAnimation_finished);

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
	set_disabled(true);
	set_position(m_hidePosition);
	set_modulate(NO_OPACITY);
	set_draw_behind_parent(true);
	set_pivot_offset(get_size() / 2);
	set_scale(INVERT_SCALE);
}

void InteractButton::display()
{
	set_visible(true);

	m_tween->connect("tween_all_completed", this, "on_displayAnimation_finished");

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
	set_mouse_filter(Control::MOUSE_FILTER_IGNORE);
	set_disabled(true);

	m_tween->interpolate_property(this, "rect_position", m_displayPosition, m_hidePosition, m_animationDuration,
		Tween::TRANS_LINEAR, Tween::EASE_OUT);
	m_tween->start();

	m_tween->interpolate_property(this, "modulate", FULL_OPACITY, NO_OPACITY, m_animationDuration,
		Tween::TRANS_LINEAR, Tween::EASE_OUT);
	m_tween->start();

	m_animationPlayer->play_backwards("turn_around");
}

bool InteractButton::isDisplayed() const
{
	return get_position() == m_displayPosition;
}

bool InteractButton::isHided() const
{
	return get_position() == getHidePosition();
}

void InteractButton::on_displayAnimation_finished()
{
	m_tween->disconnect("tween_all_completed", this, "on_displayAnimation_finished");
	set_mouse_filter(Control::MOUSE_FILTER_STOP);
	set_disabled(false);
}

void InteractButton::setHidePosition(const godot::Vector2 newPosition)
{
	m_hidePosition = newPosition;
}

godot::Vector2 InteractButton::getHidePosition() const
{
	return m_hidePosition;
}

void InteractButton::setDisplayPosition(const godot::Vector2 newPosition)
{
	m_displayPosition = newPosition;
}

godot::Vector2 InteractButton::getDisplayPosition() const
{
	return m_displayPosition;
}

void InteractButton::setAnimationDuration(const real_t newDuration)
{
	if (newDuration <= MIN_ANIMATION_DURATION)
		m_animationDuration = MIN_ANIMATION_DURATION;
	else
		m_animationDuration = newDuration;
}

real_t InteractButton::getAnimationDuation() const
{
	return m_animationDuration;
}

InteractButton::InteractButton()
{
	m_tween = nullptr;
	m_animationPlayer = nullptr;
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