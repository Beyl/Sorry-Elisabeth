#include "InteractionTable.h"

using namespace godot;

void InteractionTable::_register_methods()
{
	register_method("_ready", &InteractionTable::_ready);

	register_property<InteractionTable, Array>("Interactions", &InteractionTable::setInteractions,
		&InteractionTable::getInteractions, Array());
}

void InteractionTable::_ready()
{
	// Get children
	m_vBox = get_node("VBoxContainer")->cast_to<VBoxContainer>(get_node("VBoxContainer"));
	m_tween = get_node("Tween")->cast_to<Tween>(get_node("Tween"));

	// Scene initialisation

	// Add the interactions given in properties to the scene, and calculate the new size of it
	addInteractionsToScene();

	m_animationDuration = real_t(0.5);
	set_modulate(HIDE_MODULATE);

	// Scale initialisation
	const Vector2 parentScale = get_parent()->cast_to<Node2D>(get_parent())->get_scale();
	m_full_scale = Vector2(1 / parentScale.x, 1 / parentScale.y);
	set_pivot_offset(Vector2(get_size().x / 2, get_size().y / 2));
	set_scale(NO_SCALE);
}

void InteractionTable::display()
{
	set_visible(true);

	m_tween->interpolate_property(this, "rect_scale", NO_SCALE, m_full_scale, m_animationDuration,
		Tween::TRANS_QUART, Tween::EASE_OUT);
	m_tween->start();
	m_tween->interpolate_property(this, "modulate", HIDE_MODULATE, DISPLAY_MODULATE, m_animationDuration,
		Tween::TRANS_LINEAR, Tween::EASE_OUT);
	m_tween->start();
}

void InteractionTable::hide()
{
	m_tween->interpolate_property(this, "rect_scale", m_full_scale, NO_SCALE, m_animationDuration,
		Tween::TRANS_QUART, Tween::EASE_IN_OUT);
	m_tween->start();
	m_tween->interpolate_property(this, "modulate", DISPLAY_MODULATE, HIDE_MODULATE, m_animationDuration,
		Tween::TRANS_QUART, Tween::EASE_IN_OUT);
	m_tween->start();
}

bool InteractionTable::isDisplayed() const
{
	return get_scale() == m_full_scale;
}

bool InteractionTable::isHided() const
{
	return get_modulate() == HIDE_MODULATE;
}

int InteractionTable::getInteractionsNumber() const
{
	return int(m_vBox->get_child_count());
}

void InteractionTable::addInteractionsToScene()
{
	// Remove the previous interactions if there was inside;
	if (getInteractionsNumber() > 0) {
		for (int child = 0; child < m_vBox->get_child_count(); child++) {
			Node2D* interaction = m_vBox->get_children()[child];
			interaction->queue_free();
		}
	}

	// Then add the new ones
	for (int interaction = 0; interaction < m_interactions.size(); interaction++) {
		Ref<PackedScene> interactionScene = m_interactions[interaction];
		if (interactionScene != 0)
			m_vBox->add_child(interactionScene->instance());
	}
}

void InteractionTable::setTableSize()
{
	m_vBox->set_size(Vector2(m_vBox->get_size().x, MIN_VBOX_SIZE * getInteractionsNumber()));
	set_size(Vector2(get_size().x, (MIN_VBOX_SIZE * getInteractionsNumber() + VBOX_MARGIN * 2)));
	m_vBox->set_position(Vector2(VBOX_MARGIN, VBOX_MARGIN));
}



void InteractionTable::setInteractions(const godot::Array newInteractions)
{
	m_interactions = newInteractions;
}

godot::Array InteractionTable::getInteractions() const
{
	return m_interactions;
}

InteractionTable::InteractionTable()
{
	m_vBox = 0;
	m_tween = 0;
	m_animationDuration = 0;
	m_full_scale = Vector2();
}

InteractionTable::~InteractionTable()
{
}

void InteractionTable::_init()
{
}
