#include "FadeBackground.h"

using namespace godot;

void FadeBackground::_register_methods()
{
	register_method("_ready", &FadeBackground::_ready);
	register_method("on_fadeIn_finished", &FadeBackground::on_fadeIn_finished);
	register_method("on_fadeOut_finished", &FadeBackground::on_fadeOut_finished);

	register_property<FadeBackground, float>("Display opacity", &FadeBackground::setDisplayOpacity,
		&FadeBackground::getDisplayOpacity, 0);
	register_property<FadeBackground, real_t>("Fade duration", &FadeBackground::setFadeDuration,
		&FadeBackground::getFadeDuration, real_t(0.1));
}

void FadeBackground::_ready()
{
	// Get children
	m_tween = get_node("Tween")->cast_to<Tween>(get_node("Tween"));

	// Scene initialisation
	m_displayColor = Color(0, 0, 0, m_displayOpacity);
	set_frame_color(HIDE_COLOR);
	set_global_position(Vector2(0, 0));
	set_size(Vector2(Utils::SCREEN_WIDTH, Utils::SCREEN_HEIGHT));

	// Signal initialisation
	add_user_signal("fadeIn_finished");
	add_user_signal("fadeOut_finished");
}

void FadeBackground::fadeIn()
{
	m_tween->connect("tween_all_completed", this, "on_fadeIn_finished");

	m_tween->interpolate_property(this, "color", HIDE_COLOR, m_displayColor, m_fadeDuration,
		Tween::TRANS_LINEAR, Tween::EASE_IN_OUT);
	m_tween->start();
}

void FadeBackground::fadeOut()
{
	m_tween->connect("tween_all_completed", this, "on_fadeOut_finished");

	m_tween->interpolate_property(this, "color", m_displayColor, HIDE_COLOR, m_fadeDuration,
		Tween::TRANS_LINEAR, Tween::EASE_IN_OUT);
	m_tween->start();
}

bool FadeBackground::isDisplayed() const
{
	return get_frame_color() == m_displayColor;
}

bool FadeBackground::isHided() const
{
	return get_frame_color() == HIDE_COLOR;
}

void FadeBackground::on_fadeIn_finished()
{
	m_tween->disconnect("tween_all_completed", this, "on_fadeIn_finished");
	emit_signal("fadeIn_finished");
}

void FadeBackground::on_fadeOut_finished()
{
	m_tween->disconnect("tween_all_completed", this, "on_fadeOut_finished");
	emit_signal("fadeOut_finished");
}

void FadeBackground::setDisplayOpacity(const float newOpacity)
{
	if (newOpacity <= MIN_DISPLAY_OPACITY)
		m_displayOpacity = float(MIN_DISPLAY_OPACITY);
	else if (newOpacity > MAX_DISPLAY_OPACITY)
		m_displayOpacity = float(MAX_DISPLAY_OPACITY);
	else
		m_displayOpacity = newOpacity;
}

float FadeBackground::getDisplayOpacity() const
{
	return m_displayOpacity;
}

void FadeBackground::setFadeDuration(const real_t newDuration)
{
	if (newDuration <= real_t(MIN_FADE_DURATION))
		m_fadeDuration = real_t(MIN_FADE_DURATION);
	else
		m_fadeDuration = newDuration;
}

real_t FadeBackground::getFadeDuration() const
{
	return m_fadeDuration;
}

FadeBackground::FadeBackground()
{
	m_tween = 0;
	m_displayOpacity = 0.0;
	m_fadeDuration = 0;
	m_displayColor = Color(0, 0, 0);
}

FadeBackground::~FadeBackground()
{
}

void FadeBackground::_init()
{
}