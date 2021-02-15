#include "Room.h"

using namespace godot;

void Room::_register_methods()
{
	register_method("_ready", &Room::_ready);
	register_method("on_interaction_just_played", &Room::on_interaction_just_played);
	register_method("on_interaction_finished", &Room::on_interaction_finished);
}

void Room::_ready()
{
	// Get children
	getInteractiveObjects();	// Get the interactive objects in the array
	
	// Scene initialisation
	m_player = nullptr;
	m_playerIsInteracting = false;
	setLightIsOn(false);

	// Signals initialisation
	connectInteractionSignal();
	add_user_signal("door_opened");
}

void Room::getInteractiveObjects()
{
	for (int i = 0; i < get_child_count(); i++) {
		if (get_child(i)->get_name().find(INTERACTIVE_OBJECT_NAME_PART) != -1) {
			m_interactiveObjects.append(get_child(i)->cast_to<InteractiveObject>(get_child(i)));
		}
	}
}

void Room::connectInteractionSignal()
{
	for (int i = 0; i < m_interactiveObjects.size(); i++) {
		InteractiveObject* currentObject = m_interactiveObjects[i];
		currentObject->connect("interaction_just_played", this, "on_interaction_just_played");
		currentObject->connect("interaction_finished", this, "on_interaction_finished");
	}
}

void Room::manageInteractions()
{
	for (int i = 0; i < m_interactiveObjects.size(); i++) {
		InteractiveObject* currentObject = m_interactiveObjects[i];

		if (canInteract(currentObject))
			currentObject->displayInteractButton();
		else
			currentObject->hideAll();
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
}

bool Room::isLightTurnOn() const
{
	return m_lightIsOn;
}

void Room::on_interaction_just_played()
{
	m_playerIsInteracting = true;
}

void Room::on_interaction_finished()
{
	m_playerIsInteracting = false;
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

Room::Room()
{
	m_interactiveObjects = godot::Array();
	m_player = nullptr;
	m_playerIsInteracting = false;
	m_lightIsOn = false;
}

Room::~Room()
{
}

void Room::_init()
{
}
