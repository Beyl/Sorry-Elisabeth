#include "Interaction.h"

using namespace godot;

void Interaction::_ready()
{
	//Get children
	m_tween = get_node("Tween")->cast_to<Tween>(get_node("Tween"));
	m_label = get_node("Label")->cast_to<Label>(get_node("Label"));

	//Signal connection
	connect("button_up", this, "on_button_released");

	//Scene initialisation
	m_label->set_text(m_interactionName);
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
	// ! To modify ! "this" -> parent
	m_tween->interpolate_property(this, "rect_scale", get_scale(), Vector2(0, 0),
		real_t(m_hidingDuration), Tween::TRANS_BACK, Tween::EASE_IN);
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

void Interaction::setInteractionName(godot::String newName)
{
	if (newName.length() > MAX_NAME_CHAR) {
		m_interactionName = "Interaction";
		Godot::print("The interaction name is too long");
	}
	else if (newName.empty()) {
		m_interactionName = "Interaction";
		Godot::print("The interaction name is empty");
	}
	else
		m_interactionName = newName;
}

godot::String Interaction::getInteractionName()
{
	return m_interactionName;
}

Interaction::Interaction()
{
	m_tween = 0;
	m_label = 0;
	m_hidingDuration = 0;
}

Interaction::~Interaction()
{
}