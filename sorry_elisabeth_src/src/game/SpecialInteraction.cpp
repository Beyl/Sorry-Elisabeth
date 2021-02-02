#include "SpecialInteraction.h"

using namespace godot;

void SpecialInteraction::_register_methods()
{
	register_method("_ready", &SpecialInteraction::_ready);
	register_method("on_specialSound_played", &SpecialInteraction::on_specialSound_played);
	register_method("on_fadeIn_finished", &SpecialInteraction::on_fadeIn_finished);
	register_method("on_fadeOut_finished", &SpecialInteraction::on_fadeOut_finished);

	register_property<SpecialInteraction, Ref<AudioStreamSample>>("Special sound", &SpecialInteraction::setSpecialSound,
		&SpecialInteraction::getSpecialSound, 0);
	register_property<SpecialInteraction, Array>("Next state interactions", &SpecialInteraction::setNextInteractions,
		&SpecialInteraction::getNextInteractions, Array());
}

void SpecialInteraction::_ready()
{
	// Get children
	m_fadeBackground = get_node("CanvasLayer/FadeBackground")->cast_to<FadeBackground>(get_node("CanvasLayer/FadeBackground"));
	m_specialSoundPlayer = get_node("ObjectSpecialSoundPlayer")->cast_to<AudioStreamPlayer>(get_node("ObjectSpecialSoundPlayer"));

	// Scene initialisation
	if (m_specialSound != 0) {
		m_specialSoundPlayer->set_stream(m_specialSound);
	}
	m_fadeBackground->set_global_position(Vector2(0, 0));

	// Signal initialisation
	m_specialSoundPlayer->connect("finished", this, "on_specialSound_played");
	m_fadeBackground->connect("fadeIn_finished", this, "on_fadeIn_finished");
	m_fadeBackground->connect("fadeOut_finished", this, "on_fadeOut_finished");
}

void SpecialInteraction::play()
{
	m_fadeBackground->fadeIn();
}

void SpecialInteraction::on_fadeIn_finished()
{
	if (m_specialSound != 0)
		m_specialSoundPlayer->play();

	// Increase parent interactive object state
	InteractiveObject* parentObject = get_node(PARENT_INTERACTIVE_OBJECT_PATH)->cast_to<InteractiveObject>
		(get_node(PARENT_INTERACTIVE_OBJECT_PATH));
	parentObject->increaseState(m_nextInteractions, this);
}

void SpecialInteraction::on_specialSound_played()
{
	m_fadeBackground->fadeOut();
}

void SpecialInteraction::on_fadeOut_finished()
{
	ExamineInteraction::play();
}

void SpecialInteraction::setSpecialSound(const godot::Ref<godot::AudioStreamSample> newSound)
{
	m_specialSound = newSound;
}

godot::Ref<godot::AudioStreamSample> SpecialInteraction::getSpecialSound() const
{
	return m_specialSound;
}

void SpecialInteraction::setNextInteractions(const godot::Array newInteractions)
{
	m_nextInteractions = newInteractions;
}

godot::Array SpecialInteraction::getNextInteractions() const
{
	return m_nextInteractions;
}

SpecialInteraction::SpecialInteraction()
{
	m_fadeBackground = 0;
	m_specialSoundPlayer = 0;
}

SpecialInteraction::~SpecialInteraction()
{
}

void SpecialInteraction::_init()
{
}