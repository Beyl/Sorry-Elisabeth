#include "InteractionTable.h"

using namespace godot;

void InteractionTable::_register_methods()
{
	register_method("_ready", &InteractionTable::_ready);
}

void InteractionTable::_ready()
{
	m_vBox = get_node("VBoxContainer")->cast_to<VBoxContainer>(get_node("VBoxContainer"));
	m_tween = get_node("Tween")->cast_to<Tween>(get_node("Tween"));
	m_animationDuration = real_t(0.5);

	set_pivot_offset(Vector2(get_size().x / 2, get_size().y / 2));
	set_scale(FULL_SCALE);

	//Sizes and positions initialisation
	m_vBox->set_size(Vector2(m_vBox->get_size().x, MIN_VBOX_SIZE * m_vBox->get_child_count()));
	set_size(Vector2(get_size().x, (MIN_VBOX_SIZE * m_vBox->get_child_count() + VBOX_MARGIN * 2)));

	m_vBox->set_position(Vector2(VBOX_MARGIN, VBOX_MARGIN));
}

void InteractionTable::display()
{
	m_tween->interpolate_property(this, "rect_scale", NO_SCALE, FULL_SCALE, m_animationDuration,
		Tween::TRANS_BOUNCE, Tween::EASE_OUT);
	m_tween->start();
	m_tween->interpolate_property(this, "modulate", HIDE_MODULATE, DISPLAY_MODULATE, m_animationDuration,
		Tween::TRANS_QUART, Tween::EASE_OUT);
	m_tween->start();
}

void InteractionTable::hide()
{
	m_tween->interpolate_property(this, "rect_scale", FULL_SCALE, NO_SCALE, m_animationDuration,
		Tween::TRANS_QUART, Tween::EASE_IN_OUT);
	m_tween->start();
	m_tween->interpolate_property(this, "modulate", DISPLAY_MODULATE, HIDE_MODULATE, m_animationDuration,
		Tween::TRANS_QUART, Tween::EASE_IN_OUT);
	m_tween->start();
}

InteractionTable::InteractionTable()
{
	m_vBox = 0;
	m_tween = 0;
	m_animationDuration = 0;
}

InteractionTable::~InteractionTable()
{
}

void InteractionTable::_init()
{
}
