#include "DialogBox.h"

using namespace godot;

void DialogBox::_register_methods()
{
	register_method("_ready", &DialogBox::_ready);
	register_method("on_beforeHideTimer_timeout", &DialogBox::on_beforeHideTimer_timeout);
	register_method("on_textDisplayed", &DialogBox::on_textDisplayed);
	register_method("on_displayAnimation_completed", &DialogBox::on_displayAnimation_completed);

	register_property<DialogBox, real_t>("Text display duration",
		&DialogBox::setTextDisplayDuration, &DialogBox::getTextDisplayDuration, MIN_TEXT_DISPLAY_DURATION);
	register_property<DialogBox, real_t>("Transition display duation",
		&DialogBox::setTransitionDisplayDuration, &DialogBox::getTransitionDisplayDuration, MIN_TRANSITION_DISPLAY_DURATION);
	register_property<DialogBox, real_t>("Time before hiding", &DialogBox::setBeforeHidingDuration,
		&DialogBox::getBeforeHidingDuration, MIN_BEFORE_HIDING_DURATION);
}

void DialogBox::_ready()
{
	//Get children
	m_textLabel = get_node("RichTextLabel")->cast_to<RichTextLabel>(get_node("RichTextLabel"));
	m_boxTween = get_node("TweenDialog")->cast_to<Tween>(get_node("TweenDialog"));
	m_textTween = get_node("RichTextLabel/TweenText")->cast_to<Tween>(get_node("RichTextLabel/TweenText"));
	m_beforeHideTimer = get_node("BeforeHiding")->cast_to<Timer>(get_node("BeforeHiding"));

	//Scene initilisation
	m_textLabel->set_percent_visible(0);
	m_displayPosition = Vector2(X_DISPLAY_POSITION, Y_DISPLAY_POSITION);
	m_hidePosition = Vector2(get_position().x, Utils::ROOM_HEIGHT_ENDING + 50);
	set_position(m_hidePosition);
	m_beforeHideTimer->set_wait_time(m_beforeHidingDuration);

	//Signals connections
	m_beforeHideTimer->connect("timeout", this, "on_beforeHideTimer_timeout");
	m_textTween->connect("tween_all_completed", this, "on_textDisplayed");
}

void DialogBox::display()
{
	if (isHided()) {
		m_textLabel->set_percent_visible(0);

		m_boxTween->connect("tween_all_completed", this, "on_displayAnimation_completed");
		m_boxTween->interpolate_property(this, "rect_position", get_position(), m_displayPosition,
			m_transitionDisplayDuration, Tween::TRANS_BOUNCE, Tween::EASE_OUT);
		m_boxTween->start();
	}
}

void DialogBox::on_displayAnimation_completed()
{
	m_textTween->interpolate_property(m_textLabel, "percent_visible", 0, 1, m_textDisplayDuration, Tween::TRANS_LINEAR);
	m_textTween->start();
}

void DialogBox::on_textDisplayed()
{
	m_beforeHideTimer->start();
}

void DialogBox::on_beforeHideTimer_timeout()
{
	hide();
}

void DialogBox::hide()
{
	m_boxTween->disconnect("tween_all_completed", this, "on_displayAnimation_completed");
	m_boxTween->interpolate_property(this, "rect_position", m_displayPosition, m_hidePosition,
		m_transitionDisplayDuration, Tween::TRANS_LINEAR, Tween::EASE_IN);
	m_boxTween->start();
}

bool DialogBox::isHided()
{
	return get_position() == m_hidePosition;
}


void DialogBox::setDisplayedText(godot::String displayedText)
{
	m_textLabel->set_bbcode("[center]" + displayedText + "[/center]");
}

godot::Vector2 DialogBox::getDisplayPosition()
{
	return m_displayPosition;
}

godot::Timer* DialogBox::getBeforeHideTimer()
{
	return m_beforeHideTimer;
}

void DialogBox::setTextDisplayDuration(real_t newDuration)
{
	if (newDuration < MIN_TEXT_DISPLAY_DURATION)
		m_textDisplayDuration = MIN_TEXT_DISPLAY_DURATION;
	else
		m_textDisplayDuration = newDuration;
}

real_t DialogBox::getTextDisplayDuration()
{
	return m_textDisplayDuration;
}

void DialogBox::setTransitionDisplayDuration(real_t newDuration)
{
	if (newDuration < MIN_TRANSITION_DISPLAY_DURATION)
		m_transitionDisplayDuration = MIN_TRANSITION_DISPLAY_DURATION;
	else
		m_transitionDisplayDuration = newDuration;
}

real_t DialogBox::getTransitionDisplayDuration()
{
	return m_transitionDisplayDuration;
}

void DialogBox::setBeforeHidingDuration(real_t newDuration)
{
	if (newDuration < MIN_BEFORE_HIDING_DURATION)
		m_beforeHidingDuration = MIN_BEFORE_HIDING_DURATION;
	else
		m_beforeHidingDuration = newDuration;
}

real_t DialogBox::getBeforeHidingDuration()
{
	return m_beforeHidingDuration;
}


DialogBox::DialogBox()	
{
	m_textDisplayDuration = MIN_TEXT_DISPLAY_DURATION;
	m_transitionDisplayDuration = MIN_TRANSITION_DISPLAY_DURATION;
	m_beforeHidingDuration = MIN_BEFORE_HIDING_DURATION;

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