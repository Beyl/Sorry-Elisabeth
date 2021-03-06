#include "Interaction.h"

using namespace godot;

void Interaction::_ready()
{
	// Get children
	m_label = get_node("Label")->cast_to<Label>(get_node("Label"));
	m_objectSoundPlayer = get_node("ObjectSoundPlayer")->cast_to<AudioStreamPlayer2D>
		(get_node("ObjectSoundPlayer"));

	// Signals initialisation
	connect("button_up", this, "on_button_released");
	add_user_signal("interaction_just_played");
	add_user_signal("interaction_finished");
	connect("interaction_finished", get_node(PARENT_INTERACTIVE_OBJECT_PATH), "on_interaction_finished");
	connect("interaction_just_played", get_node(PARENT_INTERACTIVE_OBJECT_PATH), "on_interaction_just_played");

	// Scene initialisation
	set_disabled(false);
	m_label->set_text(m_interactionName);

	if (m_objectSound != nullptr) {
		m_objectSoundPlayer->set_stream(m_objectSound);
	}
}

void Interaction::on_button_released()
{
	if (m_objectSound != nullptr) {
		m_objectSoundPlayer->play();
	}
}

void Interaction::setInteractionName(const godot::String newName)
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

godot::String Interaction::getInteractionName() const
{
	return m_interactionName;
}

void Interaction::setObjectSound(const godot::Ref<godot::AudioStreamSample> newSound)
{
	m_objectSound = newSound;
}

godot::Ref<godot::AudioStreamSample> Interaction::getObjectSound() const
{
	return m_objectSound;
}

Interaction::Interaction()
{
	m_label = nullptr;
	m_objectSoundPlayer = nullptr;
	m_interactionName = String();
}

Interaction::~Interaction()
{
}