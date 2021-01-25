#include "ExamineInteraction.h"

using namespace godot;

void ExamineInteraction::_register_methods()
{
	register_method("_ready", &ExamineInteraction::_ready);
	register_method("on_button_released", &ExamineInteraction::on_button_released);

	register_property<ExamineInteraction, real_t>("Hiding duration", &Interaction::setHidingDuration,
		&Interaction::getHidingDuration, 0);
	register_property<ExamineInteraction, godot::String>("Interaction name", &Interaction::setInteractionName,
		&Interaction::getInteractionName, "Interaction");
	register_property<ExamineInteraction, String>("Examine text", &ExamineInteraction::setExamineText,
		&ExamineInteraction::getExamineText, "Insert texte here");
}

void ExamineInteraction::_ready()
{
	Interaction::_ready();

	//Get children
	m_dialogBox = get_node("CanvasLayer/DialogBox")->cast_to<DialogBox>(get_node("CanvasLayer/DialogBox"));
	m_examinationSoundPlayer = get_node("ExaminationSoundPlayer")->cast_to<AudioStreamPlayer>
		(get_node("ExaminationSoundPlayer"));

	//Scene initialisation
	m_dialogBox->setDisplayedText(m_examineText);
	m_dialogBox->setTextDisplayDuration(m_examinationSoundPlayer->get_stream()->get_length() / 2);
}

void ExamineInteraction::play()
{
	m_dialogBox->display();
	m_examinationSoundPlayer->play();
}

void ExamineInteraction::on_button_released()
{
	Interaction::on_button_released();
	play();
}

void ExamineInteraction::setExamineText(godot::String newText)
{
	m_examineText = newText;
}

godot::String ExamineInteraction::getExamineText()
{
	return m_examineText;
}

ExamineInteraction::ExamineInteraction()
{
	m_examineText = "";
	m_dialogBox = 0;
	m_examinationSoundPlayer = 0;
}

ExamineInteraction::~ExamineInteraction()
{
}

void ExamineInteraction::_init()
{
}