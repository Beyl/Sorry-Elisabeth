#include "Interaction.h"

using namespace godot;

void Interaction::_ready()
{
	//Get children
	m_tween = get_node("Tween")->cast_to<Tween>(get_node("Tween"));
	m_label = get_node("Label")->cast_to<Label>(get_node("Label"));
	m_objectSoundPlayer = get_node("InteractionSoundPlayer")->cast_to<AudioStreamPlayer2D>
		(get_node("InteractionSoundPlayer"));

	//Signal connection
	connect("button_up", this, "on_button_released");

	//Scene initialisation
	set_disabled(false);
	m_label->set_text(m_interactionName);

	if (m_objectSound != 0) {
		m_objectSoundPlayer->set_stream(m_objectSound);
	}
}

void Interaction::on_button_released()
{
	if (m_objectSound != 0) {
		m_objectSoundPlayer->play();
	}
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

void Interaction::setObjectSound(godot::Ref<godot::AudioStreamSample> newSound)
{
	m_objectSound = newSound;
}

godot::Ref<godot::AudioStreamSample> Interaction::getObjectSound()
{
	return m_objectSound;
}

Interaction::Interaction()
{
	m_tween = 0;
	m_label = 0;
	m_objectSoundPlayer = 0;
	m_interactionName = String();
}

Interaction::~Interaction()
{
}