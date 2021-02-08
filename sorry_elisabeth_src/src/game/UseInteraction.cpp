#include "UseInteraction.h"

using namespace godot;

void UseInteraction::_register_methods()
{
	register_method("_ready", &UseInteraction::_ready);

	register_property<UseInteraction, Array>("Next object interactions", &UseInteraction::setNextInteractions,
		&UseInteraction::getNextInteractions, Array());
	register_property<UseInteraction, String>("Use failed text", &UseInteraction::setUseFailedExaminationText,
		&UseInteraction::getUseFailedExaminationText, "Insert text");
	register_property<UseInteraction, Ref<AudioStreamSample>>("Use failed sound", &UseInteraction::setUseFailedSound,
		&UseInteraction::getUseFailedSound, 0);
}

void UseInteraction::_ready()
{
	m_parentInteractiveObject = get_node(PARENT_INTERACTIVE_OBJECT_PATH)->cast_to<InteractiveObject>
		(get_node(PARENT_INTERACTIVE_OBJECT_PATH));
}

void UseInteraction::play()
{
	m_inventory->enableUseMode(this);
	m_inventory->get_parent()->cast_to<InventoryButton>(m_inventory->get_parent())->on_button_released();
}

void UseInteraction::playFailedExamination()
{
	if (m_failedSound != 0) {
		m_examinationSoundPlayer->set_stream(m_failedSound);
	}
	m_dialogBox->setDisplayedText(m_useFailedText);
	m_dialogBox->setTextDisplayDuration(m_examinationSoundPlayer->get_stream()->get_length() / 2);

	ExamineInteraction::play();
}

void UseInteraction::playSucceededExamination()
{
	if (m_examinationSound != 0) {
		m_examinationSoundPlayer->set_stream(m_examinationSound);
	}
	m_dialogBox->setDisplayedText(m_examineText);
	m_dialogBox->setTextDisplayDuration(m_examinationSoundPlayer->get_stream()->get_length() / 2);

	ExamineInteraction::play();
}

void UseInteraction::setInventory(Inventory* newInventory)
{
	m_inventory = newInventory;
}

void UseInteraction::setNextInteractions(const godot::Array newInteractions)
{
	m_nextInteractions = newInteractions;
}

godot::Array UseInteraction::getNextInteractions() const
{
	return m_nextInteractions;
}

void UseInteraction::setUseFailedExaminationText(const godot::String newText)
{
	m_useFailedText = newText;
}

godot::String UseInteraction::getUseFailedExaminationText() const
{
	return m_useFailedText;
}

void UseInteraction::setUseFailedSound(const godot::Ref<godot::AudioStreamSample> newSound)
{
	m_failedSound = newSound;
}

godot::Ref<godot::AudioStreamSample> UseInteraction::getUseFailedSound() const
{
	return m_failedSound;
}

UseInteraction::UseInteraction()
{
	m_inventory = 0;
	m_parentInteractiveObject = 0;
	m_useFailedText = String();
}

UseInteraction::~UseInteraction()
{
}

void UseInteraction::_init()
{
}