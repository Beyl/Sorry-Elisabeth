#include "Room.h"
#include "Light.h"
#include "Item.h"

using namespace godot;

void Room::_register_methods()
{
	register_method("_ready", &Room::_ready);
	register_method("on_interaction_just_played", &Room::on_interaction_just_played);
	register_method("on_interaction_finished", &Room::on_interaction_finished);
	register_method("on_itemOpenInteraction_just_played", &Room::on_itemOpenInteraction_just_played);
	register_method("on_itemOpenInteraction_finished", &Room::on_itemOpenInteraction_finished);
}

void Room::_ready()
{
	// Get children
	getInteractiveObjects(this);	// Get the interactive objects in the array
	getLights();	// Same for the lights

	// Scene initialisation
	m_player = nullptr;
	m_playerIsInteracting = false;
	m_isOpenInteracting = false;
	setLightIsOn(false);

	// Signals initialisation
	add_user_signal("door_opened");
	add_user_signal("interaction_just_played");
	add_user_signal("interaction_finished");
}

void Room::clearAndGetInteractiveObjects()
{
	if (m_interactiveObjects.size() > 0)
		m_interactiveObjects.clear();

	getInteractiveObjects(this);
}

void Room::getInteractiveObjects(Node* node)
{
	bool hasBeenAdded = false;

	if (node->get_name().find(INTERACTIVE_OBJECT_NAME_PART) != -1 ||
		node->get_name().find(ITEM_NODE_NAME_PART) != -1) {

		m_interactiveObjects.append(node->cast_to<InteractiveObject>(node));
		connectInteractionSignals(node);

		if (node->get_name().find(ITEM_NODE_NAME_PART) != -1)
			hasBeenAdded = true;
	}

	if (!hasBeenAdded) {
		for (int i = 0; i < node->get_child_count(); i++)
			getInteractiveObjects(node->get_child(i));
	}
}

void Room::connectInteractionSignals(Node* node)
{
	if (node->get_name().find(ITEM_NODE_NAME_PART) != -1) {
		if (!node->is_connected("interaction_just_played", this, "on_itemOpenInteraction_just_played"))
			node->connect("interaction_just_played", this, "on_itemOpenInteraction_just_played");

		if (!node->is_connected("interaction_finished", this, "on_itemOpenInteraction_finished"))
			node->connect("interaction_finished", this, "on_itemOpenInteraction_finished");
	}
	else {
		if (!node->is_connected("interaction_just_played", this, "on_interaction_just_played"))
			node->connect("interaction_just_played", this, "on_interaction_just_played");

		if (!node->is_connected("interaction_finished", this, "on_interaction_finished"))
			node->connect("interaction_finished", this, "on_interaction_finished");
	}
}

void Room::getLights()
{
	for (int i = 0; i < get_child_count(); i++) {
		if (get_child(i)->get_name().find(LIGHT_NODE_NAME_PART) != -1) {
			m_lights.append(get_child(i)->cast_to<Light>(get_child(i)));
		}
	}
}

void Room::manageInteractions()
{
	clearAndGetInteractiveObjects();

	for (int i = 0; i < m_interactiveObjects.size(); i++) {
		Node* currentNodeObject = m_interactiveObjects[i];

		if (currentNodeObject->is_inside_tree() && !currentNodeObject->is_queued_for_deletion()) {

			if (currentNodeObject->get_name().find(INTERACTIVE_OBJECT_NAME_PART) != -1) {
				InteractiveObject* currentIObject = currentNodeObject->cast_to<InteractiveObject>(currentNodeObject);

				if (canInteract(currentIObject))
					currentIObject->displayInteractButton();
				else
					currentIObject->hideAll();
			}
			else {
				Item* currentItem = currentNodeObject->cast_to<Item>(currentNodeObject);

				if (currentItem->is_processing())
					currentItem->setPlayerIsInteracting(m_isOpenInteracting);
			}
		}
	}
}

bool Room::isInInteractionZone(InteractiveObject* object) const
{
	Vector2 objectRangePosition = Vector2(
		object->get_global_position().x - object->getObjectSize().x / 2 - Room::CAN_INTERACT_RANGE,
		object->get_global_position().y - object->getObjectSize().y / 2 - Room::CAN_INTERACT_RANGE);
	Vector2 objectRangeSize = Vector2(
		object->getObjectSize().x + Room::CAN_INTERACT_RANGE * 2,
		object->getObjectSize().y + Room::CAN_INTERACT_RANGE * 2);

	return Utils::isInsideObject(m_player->get_global_position(), objectRangePosition, objectRangeSize);
}

bool Room::canInteract(InteractiveObject* object) const
{
	return (!m_playerIsInteracting &&
		!m_isInventoryOpen &&
		isInInteractionZone(object) &&
		((!m_lightIsOn && !object->interactOnlyWhenLighted()) || m_lightIsOn));
}

bool Room::isPlayerInteracting() const
{
	return m_playerIsInteracting;
}

bool Room::isPlayerInside() const
{
	return m_player != nullptr;
}

void Room::setLightIsOn(const bool setOn)
{
	m_lightIsOn = setOn;

	for (int i = 0; i < m_lights.size(); i++) {
		Light* currentLight = m_lights[i];
		if (currentLight->getOnlyWhenActivated())
			currentLight->set_visible(m_lightIsOn);
	}
}

bool Room::isLightTurnOn() const
{
	return m_lightIsOn;
}

void Room::on_interaction_just_played()
{
	m_playerIsInteracting = true;
	emit_signal("interaction_just_played");
}

void Room::on_interaction_finished()
{
	m_playerIsInteracting = false;
	emit_signal("interaction_finished");
}

void Room::on_itemOpenInteraction_just_played()
{
	m_isOpenInteracting = true;
}

void Room::on_itemOpenInteraction_finished()
{
	m_isOpenInteracting = false;
}

void Room::setPlayer(Player* player)
{
	m_player = player;
}

void Room::setDoorIsOpen(const bool isOpen)
{
	if (isOpen)
		emit_signal("door_opened");

	m_doorIsOpened = isOpen;
}

bool Room::getDoorIsOpen() const
{
	return m_doorIsOpened;
}

void Room::setInventoryIsOpen(const bool isOpen)
{
	m_isInventoryOpen = isOpen;
}

Room::Room()
{
	m_interactiveObjects = godot::Array();
	m_player = nullptr;
	m_playerIsInteracting = false;
	m_isOpenInteracting = false;
	m_isInventoryOpen = false;
	m_lightIsOn = false;
}

Room::~Room()
{
}

void Room::_init()
{
}
