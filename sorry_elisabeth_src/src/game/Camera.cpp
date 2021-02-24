#include "Camera.h"

using namespace godot;

void Camera::_register_methods()
{
	// Methods
	register_method("_ready", &Camera::_ready);
	register_method("_process", &Camera::_process);
	register_method("on_room_changed", &Camera::on_room_changed);

	// Porperties
	register_property<Camera, Vector2>("Cellar position",
		&Camera::setCellarCamPosition, &Camera::getCellarCamPosition, Vector2(CELLAR_POSITION_X, 0));
	register_property<Camera, Vector2>("Living room position",
		&Camera::setLivingRoomCamPosition, &Camera::getLivingRoomCamPosition,Vector2(LIVING_ROOM_POSITION_X, 0));
	register_property<Camera, double>("Interpolation Duration", &Camera::setInterpolationDuration,
		&Camera::getInterpolationDuration, 0.1);
}

void Camera::_ready()
{
	// Get children
	m_changeRoomTween = get_node("ChangeRoomTween")->cast_to<Tween>(get_node("ChangeRoomTween"));
	m_followPlayerTween = get_node("FollowPlayerTween")->cast_to<Tween>(get_node("FollowPlayerTween"));

	// Scene initialisation
	m_playerIsInCellar = true;
	m_enableChangeRoom = false;
	setStartFollowPlayerLeft(Camera::START_FOLLOW_PLAYER_LEFT);
	setStartFollowPlayerRight(Camera::START_FOLLOW_PLAYER_RIGHT);

	// Signal initialisation
	add_user_signal("room_changed");
	m_changeRoomTween->connect("tween_all_completed", this, "on_room_changed");
}

void Camera::_process()
{
	if (isPlayerEnteringNewRoom() && m_enableChangeRoom) {
		if (m_playerIsInCellar)
			changeRoom(false);	// False mean : change to the living room
		else
			changeRoom(true);	// True mean : change to the cellar
	}

	// Make the camera follow the player when he is not in the middle of the room
	if (!m_isChangingRoom) {
		if (m_playerPosition.x < m_startFollowPlayerLeft && m_playerPosition.x > getCurrentXCamPosition())
			follow_player(Direction::LEFT);
		else if (m_playerPosition.x > m_startFollowPlayerRight &&
			m_playerPosition.x < m_startFollowPlayerRight + Camera::CHANGE_ROOM_RANGE * 2)
			follow_player(Direction::RIGHT);
	}
}

void Camera::on_room_changed()
{
	m_isChangingRoom = false;
}

void Camera::setEnableChangeRoom(const bool allow)
{
	m_enableChangeRoom = allow;
}

const bool Camera::isPlayerEnteringNewRoom()
{
	bool hasChanged = false;
	const int isInsideRoomRange = isPlayerInsideChangeRoomRange();

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

const int Camera::isPlayerInsideChangeRoomRange()
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

void Camera::changeRoom(const bool changeToCellar)
{
	m_playerIsInCellar = changeToCellar;

	// Do a linear interpolation with a tiny bounce at the end between to the new camera's position
	if (changeToCellar) {
		m_changeRoomTween->interpolate_property(this, "position", get_position(), m_cellarCamPosition,
			real_t(m_interpolationDuration), Tween::TRANS_BACK, Tween::EASE_OUT);
		m_changeRoomTween->start();
	}
	else {
		m_changeRoomTween->interpolate_property(this, "position", get_position(), m_livingRoomCamPosition,
			real_t(m_interpolationDuration), Tween::TRANS_BACK, Tween::EASE_OUT);
		m_changeRoomTween->start();
	}

	emit_signal("room_changed");
	m_isChangingRoom = true;
}

void Camera::follow_player(const Direction direction)
{
	if (direction == Direction::LEFT) {
		m_followPlayerTween->interpolate_property(this, "position", get_position(),
			Vector2(getCurrentXCamPosition() - (m_startFollowPlayerLeft - m_playerPosition.x), 0),
			2, 10, 1);
	}
	else {
		m_followPlayerTween->interpolate_property(this, "position", get_position(),
			Vector2(getCurrentXCamPosition() + (m_playerPosition.x - m_startFollowPlayerRight), 0),
			2, 10, 1);
	}
	m_followPlayerTween->start();

	align();	// Align the camera position with the player position (more fluid)
}

int Camera::getCurrentXCamPosition()
{
	if (m_playerIsInCellar)
		return Camera::CELLAR_POSITION_X;
	else
		return Camera::LIVING_ROOM_POSITION_X;
}

void Camera::setCellarCamPosition(const godot::Vector2 newPosition)
{
	m_cellarCamPosition = newPosition;
}

Vector2 Camera::getCellarCamPosition() const
{
	return m_cellarCamPosition;
}

void Camera::setLivingRoomCamPosition(const godot::Vector2 newPosition)
{
	m_livingRoomCamPosition = newPosition;
}

Vector2 Camera::getLivingRoomCamPosition() const
{
	return m_livingRoomCamPosition;
}

void Camera::setInterpolationDuration(const double newDuration)
{
	if (newDuration < 0.2)
		m_interpolationDuration = 0.2;
	else if (newDuration > 3.0)
		m_interpolationDuration = 3.0;
	else
		m_interpolationDuration = newDuration;
}

double Camera::getInterpolationDuration() const
{
	return m_interpolationDuration;
}

void Camera::setStartFollowPlayerLeft(const int newPosition)
{
		m_startFollowPlayerLeft = newPosition;
}

int Camera::getStartFollowPlayerLeft() const
{
	return m_startFollowPlayerLeft;
}

void Camera::setStartFollowPlayerRight(const int newPosition)
{
		m_startFollowPlayerRight = newPosition;
}

int Camera::getStartFollowPlayerRight() const
{
	return m_startFollowPlayerRight;
}

void Camera::setPlayerPosition(const Vector2 playerPosition)
{
	m_playerPosition = playerPosition;
}

void Camera::setPlayerDirection(const Direction newDirection)
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
	m_enableChangeRoom = false;
	m_isChangingRoom = false;

	m_cellarCamPosition = Vector2(0, 0);
	m_livingRoomCamPosition = Vector2(0, 0);

	m_changeRoomTween = nullptr;
	m_followPlayerTween = nullptr;
}

Camera::~Camera()
{
}

void Camera::_init()
{
}