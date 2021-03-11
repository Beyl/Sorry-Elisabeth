#include "SettingsButton.h"

using namespace godot;

void SettingsButton::_register_methods()
{
	register_method("_ready", &SettingsButton::_ready);
	register_method("_process", &SettingsButton::_process);

	register_method("on_button_down", &SettingsButton::on_button_down);
	register_method("on_settingsTable_just_closed", &SettingsButton::on_settingsTable_just_closed);
	register_method("on_mouse_entered", &SettingsButton::on_mouse_entered);
	register_method("on_mouse_exited", &SettingsButton::on_mouse_exited);
}

void SettingsButton::_ready()
{
	// Get children
	m_settingsTable = get_node("SettingsTable")->cast_to<SettingsTable>(get_node("SettingsTable"));
	m_fadeBackground = get_node("FadeBackground")->cast_to<FadeBackground>(get_node("FadeBackground"));

	// Scene initialisation
	set_self_modulate(QUARTER_OPACITY);
	set_process(false);
	m_fadeBackground->setFadeDuration(m_settingsTable->ANIMATION_DURATION);

	// Signals initialisation
	connect("button_down", this, "on_button_down");
	connect("mouse_entered", this, "on_mouse_entered");
	connect("mouse_exited", this, "on_mouse_exited");

	m_settingsTable->connect("just_closed", this, "on_settingsTable_just_closed");
}

void SettingsButton::_process()
{
	Vector2 mousePosition = get_global_mouse_position();

	if (Utils::isInsideArea(mousePosition, get_global_position(), get_size()))
		m_fadeBackground->set_mouse_filter(Control::MOUSE_FILTER_IGNORE);
	else
		m_fadeBackground->set_mouse_filter(Control::MOUSE_FILTER_STOP);
}

void SettingsButton::on_button_down()
{
	if (m_fadeBackground->isHided()) {
		m_fadeBackground->fadeIn();
		m_settingsTable->display();
		set_self_modulate(FULL_OPACITY);
		set_process(true);
	}
	else if (m_fadeBackground->isDisplayed())
		m_settingsTable->hide();
}

void SettingsButton::on_settingsTable_just_closed()
{
	m_fadeBackground->fadeOut();
	m_fadeBackground->set_mouse_filter(Control::MOUSE_FILTER_IGNORE);
	set_process(false);
	set_self_modulate(QUARTER_OPACITY);
}

void SettingsButton::on_mouse_entered()
{
	if (m_settingsTable->isHided())
		set_self_modulate(FULL_OPACITY);
}

void SettingsButton::on_mouse_exited()
{
	if (m_settingsTable->isHided())
		set_self_modulate(QUARTER_OPACITY);
}

SettingsButton::SettingsButton()
{
	m_settingsTable = nullptr;
	m_fadeBackground = nullptr;
}

SettingsButton::~SettingsButton()
{
}

void SettingsButton::_init()
{
}