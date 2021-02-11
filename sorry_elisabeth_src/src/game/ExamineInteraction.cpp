#include "ExamineInteraction.h"

using namespace godot;

void ExamineInteraction::_register_methods()
{
	register_method("_ready", &ExamineInteraction::_ready);
	register_method("on_button_released", &ExamineInteraction::on_button_released);
	register_method("on_dialogBox_just_hided", &ExamineInteraction::on_dialogBox_just_hided);

	register_property<ExamineInteraction, String>("Interaction name", &Interaction::setInteractionName,
		&Interaction::getInteractionName, "Interaction");
	register_property<ExamineInteraction, Ref<AudioStreamSample>>("Object Sound", &Interaction::setObjectSound,
		&Interaction::getObjectSound, Ref<AudioStreamSample>());
	
	register_property<ExamineInteraction, String>("Examine text", &ExamineInteraction::setExamineText,
		&ExamineInteraction::getExamineText, "Insert texte here");
	register_property<ExamineInteraction, Ref<AudioStreamSample>>("Examination Sound", &ExamineInteraction::setExaminationSound,
		&ExamineInteraction::getExaminationSound, Ref<AudioStreamSample>());
}

void ExamineInteraction::_ready()
{
	Interaction::_ready();

	//Get children
	m_dialogBox = get_node("DialogBoxLayer/DialogBox")->cast_to<DialogBox>(get_node("DialogBoxLayer/DialogBox"));
	m_examinationSoundPlayer = get_node("ExaminationSoundPlayer")->cast_to<AudioStreamPlayer>
		(get_node("ExaminationSoundPlayer"));

	//Scene initialisation
	if (m_examinationSound != nullptr) {
		m_examinationSoundPlayer->set_stream(m_examinationSound);
	}

	m_dialogBox->set_visible(false);
	m_dialogBox->setDisplayedText(m_examineText);
	m_dialogBox->setTextDisplayDuration(m_examinationSoundPlayer->get_stream()->get_length() / 2);
	m_dialogBox->connect("just_hided", this, "on_dialogBox_just_hided");
}

void ExamineInteraction::play()
{
	if (!m_dialogBox->getDisplayedText().empty()) {
		m_dialogBox->set_visible(true);
		m_dialogBox->display();
	}

	if (m_examinationSound != nullptr)
		m_examinationSoundPlayer->play();
}

void ExamineInteraction::on_button_released()
{
	Interaction::on_button_released();
	play();
}

void ExamineInteraction::on_dialogBox_just_hided()
{
	emit_signal("interaction_finished");
}

void ExamineInteraction::setExamineText(godot::String newText)
{
	m_examineText = newText;
}

godot::String ExamineInteraction::getExamineText() const
{
	return m_examineText;
}

void ExamineInteraction::setExaminationSound(Ref<AudioStreamSample> newSound)
{
	m_examinationSound = newSound;
}

Ref<AudioStreamSample> ExamineInteraction::getExaminationSound() const
{
	return m_examinationSound;
}

ExamineInteraction::ExamineInteraction()
{
	m_examineText = String();
	m_dialogBox = nullptr;
	m_examinationSoundPlayer = nullptr;
}

ExamineInteraction::~ExamineInteraction()
{
}

void ExamineInteraction::_init()
{
}