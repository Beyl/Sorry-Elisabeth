#include "Item.h"
#include "Cell.h"

using namespace godot;

void Item::_register_methods()
{
	register_method("_ready", &Item::_ready);
	register_method("_process", &Item::_process);
	register_method("on_interactButton_released", &Item::on_interactButton_released);
	register_method("on_interaction_just_played", &Item::on_interaction_just_played);
	register_method("on_interaction_finished", &Item::on_interaction_finished);

	register_property<Item, int>("Number of state", &InteractiveObject::setObjectStateNumber,
		&InteractiveObject::getObjectStateNumber, 0);
	register_property<Item, Vector2>("Object size", &InteractiveObject::setObjectSize,
		&InteractiveObject::getObjectSize, Vector2());
}

void Item::_ready()
{
	InteractiveObject::_ready();

	const real_t yDisplayPosition =
		m_interactButton->getHidePosition().y - Cell::CELL_SIZE / 2 - m_interactButton->get_size().y / 2 -
		Interaction::INTERACT_BUTTON_MARGIN;
	m_interactButton->setDisplayPosition(Vector2(m_interactButton->getHidePosition().x, yDisplayPosition));

	setInteractionTablePosition();
	disableOpenMode();
}

void Item::_process(float delta)
{
	const Vector2 mousePosition = get_global_mouse_position();

	const Vector2 itemMarginPosition =
		Vector2(get_global_position().x - Cell::HIDE_INTERACT_BUTTON_MARGIN_X,
			get_global_position().y - real_t(Cell::HIDE_INTERACT_BUTTON_MARGIN_Y * 1.5));
	const Vector2 itemMarginSize = Vector2(m_objectSize.x + 2 * Cell::HIDE_INTERACT_BUTTON_MARGIN_X,
		m_objectSize.y + real_t(Cell::HIDE_INTERACT_BUTTON_MARGIN_Y * 1.5));

	if (Utils::isInsideObject(mousePosition, itemMarginPosition, itemMarginSize)) {
		if (m_interactButton->isHided() && m_interactionTable->isHided())
			displayInteractButton();
	}
	else
		hideAll();
}

void Item::enableOpenMode()
{
	set_process(true);
}

void Item::disableOpenMode()
{
	set_process(false);
}

void Item::setInteractionTablePosition()
{
	const real_t yPosition = -m_interactionTable->get_size().y - Cell::CELL_SIZE / 2 - Interaction::INTERACT_BUTTON_MARGIN * 4;
	const real_t xPosition = -m_interactionTable->get_size().x / 2;
	m_interactionTable->set_position(Vector2(xPosition, yPosition));
}

InteractionTable* Item::getInteractionTable() const
{
	return m_interactionTable;
}

InteractButton* Item::getInteractButton() const
{
	return m_interactButton;
}

void Item::on_interactButton_released()
{
	m_interactButton->hide();

	m_interactionTable->setTableSize();
	setInteractionTablePosition();
	m_interactionTable->display();
}

void Item::on_interaction_just_played()
{
	emit_signal("interaction_just_played");
}

void Item::on_interaction_finished()
{
	emit_signal("interaction_finished");
}

Item::Item()
{
}

Item::~Item()
{
}

void Item::_init()
{
}