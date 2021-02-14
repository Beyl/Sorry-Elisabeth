#include "InteractiveObject.h"

using namespace godot;

void InteractiveObject::_register_methods()
{
	register_method("_ready", &InteractiveObject::_ready);
	register_method("on_interactButton_released", &InteractiveObject::on_interactButton_released);
	register_method("on_increaseTypeInteraction_finished", &InteractiveObject::on_increaseTypeInteraction_finished);
	register_method("on_interaction_just_played", &InteractiveObject::on_interaction_just_played);
	register_method("on_interaction_finished", &InteractiveObject::on_interaction_finished);

	register_property<InteractiveObject, int>("Number of state", &InteractiveObject::setObjectStateNumber,
		&InteractiveObject::getObjectStateNumber, 0);
	register_property<InteractiveObject, Vector2>("Object size", &InteractiveObject::setObjectSize,
		&InteractiveObject::getObjectSize, Vector2());	
	register_property<InteractiveObject, String>("Use item name", &InteractiveObject::setUseItemName,
		&InteractiveObject::getUseItemName, "Insert use item name");
	register_property<InteractiveObject, bool>("Interact only when lighted", &InteractiveObject::setInteractOnlyWhenLighted,
		&InteractiveObject::interactOnlyWhenLighted, NULL);
}

void InteractiveObject::_ready()
{
	// Get children
	m_interactButton = get_node("InteractButton")->cast_to<InteractButton>(get_node("InteractButton"));
	m_interactionTable = get_node("InteractionTable")->cast_to<InteractionTable>(get_node("InteractionTable"));

	// Scene initialisation
	setInteractionTablePosition();
	m_state = Utils::ASCII_CONVERSION_1;
	m_interactButton->set_visible(false);
	m_interactButton->connect("button_up", this, "on_interactButton_released");

	// Signals initialisation
	add_user_signal("interaction_just_played");
	add_user_signal("interaction_finished");
}

void InteractiveObject::setInteractionTablePosition()
{
	const real_t yPosition = -m_objectSize.y / 2 - m_interactionTable->get_size().y - Utils::INTERACT_BUTTON_MARGIN * 4;
	const real_t xPosition = -m_interactionTable->get_size().x / 2;
	m_interactionTable->set_position(Vector2(xPosition, yPosition));
}

void InteractiveObject::displayInteractButton()
{
	if (offerInteractions()) {
		if (m_interactButton->isHided() && m_interactionTable->isHided())
			m_interactButton->display();
	}
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

bool InteractiveObject::offerInteractions() const
{
	return m_interactionTable->getInteractionsNumber() > 0;
}

void InteractiveObject::increaseState(godot::Array nextInteractions, Interaction* increaseTypeInteraction)
{
	if (m_state < m_objectStateNumber + Utils::ASCII_CONVERSION_0) {
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

void InteractiveObject::on_interaction_just_played()
{
	emit_signal("interaction_just_played");
}

void InteractiveObject::on_interaction_finished()
{
	emit_signal("interaction_finished");
}

void InteractiveObject::setObjectStateNumber(const int stateNumber)
{
	m_objectStateNumber = stateNumber;
}

int InteractiveObject::getObjectStateNumber() const
{
	return m_objectStateNumber;
}

void InteractiveObject::setObjectSize(const godot::Vector2 newSize)
{
	m_objectSize = newSize;
}

godot::Vector2 InteractiveObject::getObjectSize() const
{
	return m_objectSize;
}

void InteractiveObject::setUseItemName(const godot::String newItemName)
{
	m_useItemName = newItemName;
}

godot::String InteractiveObject::getUseItemName() const
{
	return m_useItemName;
}

void InteractiveObject::setInteractOnlyWhenLighted(const bool canInteract)
{
	m_interactOnlyWhenLighted = canInteract;
}

bool InteractiveObject::interactOnlyWhenLighted() const
{
	return m_interactOnlyWhenLighted;
}


InteractiveObject::InteractiveObject()
{
	m_interactButton = nullptr;
	m_interactionTable = nullptr;
	m_state = 0;
	m_objectStateNumber = 0;
	m_interactOnlyWhenLighted = false;
}

InteractiveObject::~InteractiveObject()
{
}

void InteractiveObject::_init()
{
}