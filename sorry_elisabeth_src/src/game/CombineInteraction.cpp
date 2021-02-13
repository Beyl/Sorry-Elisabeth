#include "CombineInteraction.h"

using namespace godot;

void CombineInteraction::_register_methods()
{
	register_property<CombineInteraction, Dictionary>("Combined items", &CombineInteraction::setCombinedItems,
		&CombineInteraction::getCombinedItems, Dictionary());
	register_property<CombineInteraction, String>("Combine failed text", &CombineInteraction::setCombineFailedExaminationText,
		&CombineInteraction::getCombineFailedExaminationText, "Insert failed text");
	register_property<CombineInteraction, Ref<AudioStreamSample>>("Combine failed sound", &CombineInteraction::setCombineFailedSound,
		&CombineInteraction::getCombineFailedSound, Ref<AudioStreamSample>());
}

void CombineInteraction::play()
{
	m_inventory->enableSpecialMode(this);
}

void CombineInteraction::playFailedExamination()
{
	if (m_failedSound != nullptr) {
		m_examinationSoundPlayer->set_stream(m_failedSound);
	}
	m_dialogBox->setDisplayedText(m_combineFailedText);
	m_dialogBox->setTextDisplayDuration(m_examinationSoundPlayer->get_stream()->get_length() / 2);

	ExamineInteraction::play();
}

void CombineInteraction::playSucceededExamination()
{
	if (m_examinationSound != nullptr) {
		m_examinationSoundPlayer->set_stream(m_examinationSound);
	}
	m_dialogBox->setDisplayedText(m_examineText);
	m_dialogBox->setTextDisplayDuration(m_examinationSoundPlayer->get_stream()->get_length() / 2);

	ExamineInteraction::play();
}

void CombineInteraction::setInventory(Inventory* newInventory)
{
	m_inventory = newInventory;
}

void CombineInteraction::setCombinedItems(const godot::Dictionary newCombinedItems)
{
	m_combinedItems = newCombinedItems;
}

godot::Dictionary CombineInteraction::getCombinedItems() const
{
	return m_combinedItems;
}

void CombineInteraction::setCombineFailedExaminationText(const godot::String newText)
{
	m_combineFailedText = newText;
}

godot::String CombineInteraction::getCombineFailedExaminationText() const
{
	return m_combineFailedText;
}

void CombineInteraction::setCombineFailedSound(const godot::Ref<godot::AudioStreamSample> newSound)
{
	m_failedSound = newSound;
}

godot::Ref<godot::AudioStreamSample> CombineInteraction::getCombineFailedSound() const
{
	return m_failedSound;
}

CombineInteraction::CombineInteraction()
{
	m_inventory = nullptr;
	m_combinedItems = Dictionary();
	m_combineFailedText = String();
	m_failedSound = Ref<AudioStreamSample>();
}

CombineInteraction::~CombineInteraction()
{
}

void CombineInteraction::_init()
{
}