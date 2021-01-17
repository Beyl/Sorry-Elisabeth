#include "DialogBox.h"

using namespace godot;

void DialogBox::_register_methods()
{
	register_method("_ready", &DialogBox::_ready);
	register_method("on_beforeHideTimer_timeout", &DialogBox::on_beforeHideTimer_timeout);
	register_method("on_textDisplayed", &DialogBox::on_textDisplayed);

	register_property<DialogBox, double>("Text display duration",
		&DialogBox::setTextDisplayDuration, &DialogBox::getTextDisplayDuration,
		Utils::MIN_TEXT_DISPLAY_DURATION);
	register_property<DialogBox, double>("Transition display duation",
		&DialogBox::setTransitionDisplayDuration, &DialogBox::getTransitionDisplayDuration,
		Utils::MIN_TRANSITION_DISPLAY_DURATION);
}

void DialogBox::_ready()
{
	//Get children
	m_textLabel = get_node("RichTextLabel")->cast_to<RichTextLabel>
		(get_node("RichTextLabel"));
	m_boxTween = get_node("TweenDialog")->cast_to<Tween>(get_node("TweenDialog"));
	m_textTween = get_node("RichTextLabel/TweenText")->cast_to<Tween>
		(get_node("RichTextLabel/TweenText"));
	m_beforeHideTimer = get_node("BeforeHiding")->cast_to<Timer>(get_node("BeforeHiding"));

	//Scene initilisation
	m_textLabel->set_percent_visible(0);
	m_displayPosition = get_position();
	m_hidePosition = Vector2(get_position().x, Utils::ROOM_HEIGHT_ENDING + 50);
	set_position(m_hidePosition);

	//Signals connection
	m_beforeHideTimer->connect("timeout", this, "on_beforeHideTimer_timeout");
	m_textTween->connect("tween_all_completed", this, "on_textDisplayed");

	//Tween interpolation init
	m_textTween->interpolate_property(m_textLabel, "percent_visible", 0, 1,
		m_textDisplayDuration, Tween::TRANS_LINEAR);
	m_boxTween->interpolate_property(this, "rect_position", get_position(), m_displayPosition,
		m_transitionDisplayDuration, Tween::TRANS_BOUNCE, Tween::EASE_OUT);

	display();
}

void DialogBox::on_beforeHideTimer_timeout()
{
	hide();
}

void DialogBox::on_textDisplayed()
{
	m_beforeHideTimer->start();
}

void DialogBox::display()
{
	m_boxTween->start();
	displayText();
}

void DialogBox::displayText()
{
	m_textTween->start();
}

void DialogBox::hide()
{
	m_boxTween->interpolate_property(this, "rect_position", m_displayPosition, m_hidePosition,
		m_transitionDisplayDuration, Tween::TRANS_LINEAR, Tween::EASE_IN);
	m_boxTween->start();
}

void DialogBox::setTextDisplayDuration(double newDuration)
{
	if (newDuration < Utils::MIN_TEXT_DISPLAY_DURATION)
		m_textDisplayDuration = double(Utils::MIN_TEXT_DISPLAY_DURATION);
	else
		m_textDisplayDuration = newDuration;
}

double DialogBox::getTextDisplayDuration()
{
	return m_textDisplayDuration;
}

void DialogBox::setTransitionDisplayDuration(double newDuration)
{
	if (newDuration < Utils::MIN_TRANSITION_DISPLAY_DURATION)
		m_transitionDisplayDuration = double(Utils::MIN_TRANSITION_DISPLAY_DURATION);
	else
		m_transitionDisplayDuration = newDuration;
}

double DialogBox::getTransitionDisplayDuration()
{
	return m_transitionDisplayDuration;
}


DialogBox::DialogBox()
{
	m_textDisplayDuration = Utils::MIN_TEXT_DISPLAY_DURATION;
	m_transitionDisplayDuration = Utils::MIN_TRANSITION_DISPLAY_DURATION;

	m_boxTween = 0;
	m_textTween = 0;
	m_textLabel = 0;
	m_beforeHideTimer = 0;

	m_displayPosition = Vector2(0, 0);
	m_hidePosition = Vector2(0, 0);
}

DialogBox::~DialogBox()
{
}

void DialogBox::_init()
{
}