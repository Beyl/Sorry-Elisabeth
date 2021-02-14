#include "OpenDoorInteraction.h"

using namespace godot;

void OpenDoorInteraction::_register_methods()
{
	register_method("_ready", &OpenDoorInteraction::_ready);
	register_method("on_specialSound_played", &OpenDoorInteraction::on_specialSound_played);
	register_method("on_fadeIn_finished", &OpenDoorInteraction::on_fadeIn_finished);
	register_method("on_fadeOut_finished", &OpenDoorInteraction::on_fadeOut_finished);

	register_property<OpenDoorInteraction, Ref<AudioStreamSample>>("Special sound", &OpenDoorInteraction::setSpecialSound,
		&OpenDoorInteraction::getSpecialSound, Ref<AudioStreamSample>());
	register_property<OpenDoorInteraction, Array>("Next state interactions", &OpenDoorInteraction::setNextInteractions,
		&OpenDoorInteraction::getNextInteractions, Array());
}

void OpenDoorInteraction::_ready()
{
	// Get children
	m_fadeBackground = get_node("FadeBackgroundLayer/FadeBackground")->cast_to<FadeBackground>
		(get_node("FadeBackgroundLayer/FadeBackground"));
	m_specialSoundPlayer = get_node("ObjectSpecialSoundPlayer")->cast_to<AudioStreamPlayer>(get_node("ObjectSpecialSoundPlayer"));

	// Scene initialisation
	if (m_specialSound != nullptr) {
		m_specialSoundPlayer->set_stream(m_specialSound);
	}

	// Signal initialisation
	m_specialSoundPlayer->connect("finished", this, "on_specialSound_played");
	m_fadeBackground->connect("fadeIn_finished", this, "on_fadeIn_finished");
	m_fadeBackground->connect("fadeOut_finished", this, "on_fadeOut_finished");
}

void OpenDoorInteraction::play()
{
	emit_signal("interaction_just_played");
	m_fadeBackground->set_mouse_filter(Control::MOUSE_FILTER_STOP);
	m_fadeBackground->fadeIn();
}

void OpenDoorInteraction::on_fadeIn_finished()
{
	if (m_specialSound != nullptr)
		m_specialSoundPlayer->play();

	// Increase parent interactive object state
	InteractiveObject* parentObject = get_node(PARENT_INTERACTIVE_OBJECT_PATH)->cast_to<InteractiveObject>
		(get_node(PARENT_INTERACTIVE_OBJECT_PATH));
	parentObject->increaseState(m_nextInteractions, this);

	m_room->setDoorIsOpen(true);
}

void OpenDoorInteraction::on_specialSound_played()
{
	m_fadeBackground->fadeOut();
}

void OpenDoorInteraction::on_fadeOut_finished()
{
	m_fadeBackground->set_mouse_filter(Control::MOUSE_FILTER_IGNORE);
	ExamineInteraction::play();
}

void OpenDoorInteraction::setSpecialSound(const godot::Ref<godot::AudioStreamSample> newSound)
{
	m_specialSound = newSound;
}

godot::Ref<godot::AudioStreamSample> OpenDoorInteraction::getSpecialSound() const
{
	return m_specialSound;
}

void OpenDoorInteraction::setNextInteractions(const godot::Array newInteractions)
{
	m_nextInteractions = newInteractions;
}

godot::Array OpenDoorInteraction::getNextInteractions() const
{
	return m_nextInteractions;
}

void OpenDoorInteraction::setRoom(Room* newRoom)
{
	m_room = newRoom;
}

OpenDoorInteraction::OpenDoorInteraction()
{
	m_fadeBackground = nullptr;
	m_specialSoundPlayer = nullptr;
	m_room = nullptr;
}

OpenDoorInteraction::~OpenDoorInteraction()
{
}

void OpenDoorInteraction::_init()
{
}