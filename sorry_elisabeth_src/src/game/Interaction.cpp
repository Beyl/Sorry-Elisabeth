#include "Interaction.h"

using namespace godot;

void Interaction::_register_methods()
{
	register_method("_ready", &Interaction::_ready);
	register_method("on_button_released", &Interaction::on_button_released);

	register_property<Interaction, double>("Hiding duration", &Interaction::setHidingDuration,
		&Interaction::getHidingDuration, 0);
}

void Interaction::_ready()
{
	//Get children
	m_tween = get_node("Tween")->cast_to<Tween>(get_node("Tween"));

	//Signal connection
	connect("button_up", this, "on_button_released");
}

void Interaction::play()
{
}

void Interaction::on_button_released()
{
	hideParent();
}

void Interaction::hideParent()
{
	m_tween->interpolate_property(this, "rect_scale", get_scale(), Vector2(0, 0),
		real_t(m_hidingDuration), Tween::TRANS_EXPO, Tween::EASE_OUT);
	m_tween->start();
}

void Interaction::setHidingDuration(double newDuration)
{
	if (newDuration < 0)
		m_hidingDuration = 0.1;
	else
		m_hidingDuration = newDuration;
}

double Interaction::getHidingDuration()
{
	return m_hidingDuration;
}

Interaction::Interaction()
{
	m_tween = 0;
	m_hidingDuration = 0;
}

Interaction::~Interaction()
{
}