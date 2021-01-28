#include "InteractiveObject.h"

using namespace godot;

void InteractiveObject::_register_methods()
{
	register_method("_ready", &InteractiveObject::_ready);
	register_method("on_interactButton_released", &InteractiveObject::on_interactButton_released);
	register_method("on_increaseTypeInteraction_finished", &InteractiveObject::on_increaseTypeInteraction_finished);

	register_property<InteractiveObject, int>("Number of state", &InteractiveObject::setObjectStateNumber,
		&InteractiveObject::getObjectStateNumber, 0);
	register_property<InteractiveObject, Vector2>("Object size", &InteractiveObject::setObjectSize,
		&InteractiveObject::getObjectSize, Vector2());
}

void InteractiveObject::_ready()
{
	// Get children
	m_interactButton = get_node("InteractButton")->cast_to<InteractButton>(get_node("InteractButton"));
	m_interactionTable = get_node("InteractionTable")->cast_to<InteractionTable>(get_node("InteractionTable"));

	// Scene initialisation
	setInteractionTablePosition();
	m_state = ASCII_CONVERSION_1;
	m_interactButton->connect("button_up", this, "on_interactButton_released");
	displayInteractButton();
}

void InteractiveObject::setInteractionTablePosition()
{
	m_interactionTable->set_position(Vector2(m_interactionTable->get_position().x,
		-m_objectSize.y / 2 - m_interactionTable->get_size().y / 2 -
		(m_interactionTable->getInteractionsNumber() * (m_interactionTable->MIN_VBOX_SIZE + m_interactionTable->VBOX_MARGIN))));
}

void InteractiveObject::displayInteractButton()
{
	if (offerInteractions())
		m_interactButton->display();
	else
		m_interactButton->set_visible(false);
}

void InteractiveObject::hideAll()
{
	if (m_interactButton->isDisplayed())
		m_interactButton->hide();

	if (m_interactionTable->isDisplayed())
		m_interactionTable->hide();
}

void InteractiveObject::on_interactButton_released()
{
	m_interactButton->hide();

	m_interactionTable->setTableSize();
	setInteractionTablePosition();
	m_interactionTable->display();
}

bool InteractiveObject::offerInteractions()
{
	return m_interactionTable->getInteractionsNumber() > 0;
}

void InteractiveObject::increaseState(godot::Array nextInteractions, Interaction* increaseTypeInteraction)
{
	if (m_state <= m_objectStateNumber + ASCII_CONVERSION_1) {
		m_state++;

		set_animation("state" + String(m_state));	// Set the next animation
		hideAll();

		m_interactionTable->setInteractions(nextInteractions);
		increaseTypeInteraction->connect("interaction_finished", this, "on_increaseTypeInteraction_finished");
	}
}

void InteractiveObject::on_increaseTypeInteraction_finished()
{
	m_interactionTable->addInteractionsToScene();
}

void InteractiveObject::setObjectStateNumber(int stateNumber)
{
	m_objectStateNumber = stateNumber;
}

int InteractiveObject::getObjectStateNumber()
{
	return m_objectStateNumber;
}

void InteractiveObject::setObjectSize(godot::Vector2 newSize)
{
	m_objectSize = newSize;
}

godot::Vector2 InteractiveObject::getObjectSize()
{
	return m_objectSize;
}


InteractiveObject::InteractiveObject()
{
	m_interactButton = 0;
	m_interactionTable = 0;
	m_state = 0;
	m_objectStateNumber = 0;
}

InteractiveObject::~InteractiveObject()
{
}

void InteractiveObject::_init()
{
}