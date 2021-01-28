#include "Camera.h"

using namespace godot;

void Camera::_register_methods()
{
	// Methods
	register_method("_ready", &Camera::_ready);
	register_method("_process", &Camera::_process);

	// Porperties
	register_property<Camera, Vector2>("Cellar position",
		&Camera::setCellarCamPosition, &Camera::getCellarCamPosition, Vector2(CELLAR_POSITION_X, 0));
	register_property<Camera, Vector2>("Living room position",
		&Camera::setLivingRoomCamPosition, &Camera::getLivingRoomCamPosition,Vector2(LIVING_ROOM_POSITION_X, 0));
	register_property<Camera, double>("Interpolation Duration", &Camera::setInterpolationDuration,
		&Camera::getInterpolationDuration, 0.1);

	register_property<Camera, int>("Follow player left X position",
		&Camera::setStartFollowPlayerLeft, &Camera::getStartFollowPlayerLeft, START_FOLLOW_PLAYER_LEFT_MIN);
	register_property<Camera, int>("Follow player right X position",
		&Camera::setStartFollowPlayerRight, &Camera::getStartFollowPlayerRight, START_FOLLOW_PLAYER_RIGHT_MIN);
}

void Camera::_ready()
{
	// Member variables initalisation
	m_playerIsInCellar = true;

	// Get children
	m_tween = get_node("Tween")->cast_to<Tween>(get_node("Tween"));
}

void Camera::_process()
{
	if (isPlayerEnteringNewRoom()) {
		if (m_playerIsInCellar)
			changeRoom(false);	// False mean : change to the living room
		else
			changeRoom(true);	// True mean : change to the cellar
	}

	// Make the camera follow the player when he is in the extreme of the rooms
	if (m_playerPosition.x < m_startFollowPlayerLeft ||
		m_playerPosition.x > m_startFollowPlayerRight)
		follow_player();
}

bool Camera::isPlayerEnteringNewRoom()
{
	bool hasChanged = false;
	int isInsideRoomRange = isPlayerInsideChangeRoomRange();

	if (isInsideRoomRange == 1) {	// If the player is inside the cellar change room range
		if (m_playerDirection == Direction::RIGHT)
			hasChanged = true;
	}
	else if (isInsideRoomRange == 2) {	// If the player is inside the living room change room range
		if (m_playerDirection == Direction::LEFT)
			hasChanged = true;
	}

	return hasChanged;
}

int Camera::isPlayerInsideChangeRoomRange()
{
	int isInside = 0;

	if (m_playerIsInCellar) {
		if (m_playerPosition.x > LIVING_ROOM_POSITION_X - CHANGE_ROOM_RANGE
			&& m_playerPosition.x < LIVING_ROOM_POSITION_X)
			isInside = 1;
	}
	else {
		if (m_playerPosition.x < LIVING_ROOM_POSITION_X + CHANGE_ROOM_RANGE
			&& m_playerPosition.x > LIVING_ROOM_POSITION_X)
			isInside = 2;
	}

	return isInside;
}

void Camera::changeRoom(bool changeToCellar)
{
	m_playerIsInCellar = changeToCellar;

	// Do a linear interpolation with a tiny bounce at the end between to the new camera's position
	if (changeToCellar) {
		m_tween->interpolate_property(this, "position", get_position(), m_cellarCamPosition,
			real_t(m_interpolationDuration), Tween::TRANS_BACK, Tween::EASE_OUT);
		m_tween->start();
	}
	else {
		m_tween->interpolate_property(this, "position", get_position(), m_livingRoomCamPosition,
			real_t(m_interpolationDuration), 10, 1);
		m_tween->start();
	}
}

void Camera::follow_player()
{
	if (m_playerIsInCellar) {
		m_tween->interpolate_property(this, "position", get_position(),
			Vector2(m_cellarCamPosition.x - (m_startFollowPlayerLeft - m_playerPosition.x), 0),
			1, 10, 1);
	}
	else {
		m_tween->interpolate_property(this, "position", get_position(),
			Vector2(m_livingRoomCamPosition.x + (m_playerPosition.x - m_startFollowPlayerRight), 0),
			1, 10, 1);
	}
	m_tween->start();

	align();	// Align the camera position with the player position (more fluid)
}

void Camera::setCellarCamPosition(godot::Vector2 newPosition)
{
	m_cellarCamPosition = newPosition;
}

Vector2 Camera::getCellarCamPosition()
{
	return m_cellarCamPosition;
}

void Camera::setLivingRoomCamPosition(godot::Vector2 newPosition)
{
	m_livingRoomCamPosition = newPosition;
}

Vector2 Camera::getLivingRoomCamPosition()
{
	return m_livingRoomCamPosition;
}

void Camera::setInterpolationDuration(double newDuration)
{
	if (newDuration < 0.2)
		m_interpolationDuration = 0.2;
	else if (newDuration > 3.0)
		m_interpolationDuration = 3.0;
	else
		m_interpolationDuration = newDuration;
}

double Camera::getInterpolationDuration()
{
	return m_interpolationDuration;
}

void Camera::setStartFollowPlayerLeft(int newPosition)
{
	if (newPosition < START_FOLLOW_PLAYER_LEFT_MIN)
		m_startFollowPlayerLeft = START_FOLLOW_PLAYER_LEFT_MIN;
	else if (newPosition > START_FOLLOW_PLAYER_LEFT_MAX)
		m_startFollowPlayerLeft = START_FOLLOW_PLAYER_LEFT_MAX;
	else
		m_startFollowPlayerLeft = newPosition;
}

int Camera::getStartFollowPlayerLeft()
{
	return m_startFollowPlayerLeft;
}

void Camera::setStartFollowPlayerRight(int newPosition)
{
	if (newPosition < START_FOLLOW_PLAYER_RIGHT_MIN)
		m_startFollowPlayerRight = START_FOLLOW_PLAYER_RIGHT_MIN;
	else if (newPosition > START_FOLLOW_PLAYER_RIGHT_MAX)
		m_startFollowPlayerRight = START_FOLLOW_PLAYER_RIGHT_MAX;
	else
		m_startFollowPlayerRight = newPosition;
}

int Camera::getStartFollowPlayerRight()
{
	return m_startFollowPlayerRight;
}

void Camera::setPlayerPosition(Vector2 playerPosition)
{
	m_playerPosition = playerPosition;
}

void Camera::setPlayerDirection(Direction newDirection)
{
	m_playerDirection = newDirection;
}

Camera::Camera()
{
	m_interpolationDuration = 0;

	m_startFollowPlayerLeft = 0;
	m_startFollowPlayerRight = 0;

	m_playerIsInCellar = true;
	m_playerPosition = Vector2(0, 0);
	m_playerDirection = Direction::RIGHT;

	m_cellarCamPosition = Vector2(0, 0);
	m_livingRoomCamPosition = Vector2(0, 0);

	m_tween = 0;
}

Camera::~Camera()
{
}

void Camera::_init()
{
}