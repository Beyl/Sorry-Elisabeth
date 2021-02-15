#include "ActiveLightInteraction.h"

using namespace godot;

void ActiveLightInteraction::_register_methods()
{
	register_method("_ready", &ActiveLightInteraction::_ready);

	register_property<ActiveLightInteraction, Ref<AudioStreamSample>>("Special sound", &ActiveLightInteraction::setSpecialSound,
		&ActiveLightInteraction::getSpecialSound, Ref<AudioStreamSample>());
	register_property<ActiveLightInteraction, Array>("Next state interactions", &ActiveLightInteraction::setNextInteractions,
		&ActiveLightInteraction::getNextInteractions, Array());
}

void ActiveLightInteraction::_ready()
{
	// Get children
	m_specialSoundPlayer = get_node("ObjectSpecialSoundPlayer")->cast_to<AudioStreamPlayer>(get_node("ObjectSpecialSoundPlayer"));

	// Scene initialisation
	if (m_specialSound != nullptr) {
		m_specialSoundPlayer->set_stream(m_specialSound);
	}
}

void ActiveLightInteraction::play()
{
	if (m_specialSound != nullptr)
		m_specialSoundPlayer->play();

	// Increase parent interactive object state
	InteractiveObject* parentObject = get_node(PARENT_INTERACTIVE_OBJECT_PATH)->cast_to<InteractiveObject>
		(get_node(PARENT_INTERACTIVE_OBJECT_PATH));
	parentObject->increaseState(m_nextInteractions, this);

	m_room->setLightIsOn(true);

	ExamineInteraction::play();
}

void ActiveLightInteraction::setSpecialSound(const godot::Ref<godot::AudioStreamSample> newSound)
{
	m_specialSound = newSound;
}

godot::Ref<godot::AudioStreamSample> ActiveLightInteraction::getSpecialSound() const
{
	return m_specialSound;
}

void ActiveLightInteraction::setNextInteractions(const godot::Array newInteractions)
{
	m_nextInteractions = newInteractions;
}

godot::Array ActiveLightInteraction::getNextInteractions() const
{
	return m_nextInteractions;
}

void ActiveLightInteraction::setRoom(Room* newRoom)
{
	m_room = newRoom;
}

ActiveLightInteraction::ActiveLightInteraction()
{
	m_specialSoundPlayer = nullptr;
	m_room = nullptr;
}

ActiveLightInteraction::~ActiveLightInteraction()
{
}

void ActiveLightInteraction::_init()
{
}