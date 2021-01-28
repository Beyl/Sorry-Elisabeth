#include "player.h"

using namespace godot;

void Player::_register_methods()
{
	register_method("_ready", &Player::_ready);
	register_method("_physics_process", &Player::_physics_process);

	register_property<Player, int>("Speed", &Player::setSpeed, &Player::getSpeed, MIN_SPEED);
}

void Player::_ready()
{
	// Get the children nodes
	m_animSprite = get_node("AnimatedSprite")->cast_to<AnimatedSprite>(get_node("AnimatedSprite"));

	// Initialisation of the scene
	m_direction = Direction::RIGHT;
	stopMooving();	// The player doesn't moove when entering a scene
}

void Player::_physics_process()
{
	if (m_xDestination != NO_DESTINATION) {		// If the player is mooving

		if (m_direction == Direction::RIGHT) {
			if (get_position().x >= m_xDestination)	// If he reached the destination then set stop him
				stopMooving();
			else
				move_and_slide(Vector2(real_t(m_speed), 0));	// Otherwise make him moove
		}

		else {
			if (get_position().x <= m_xDestination)
				stopMooving();
			else
				move_and_slide(Vector2(real_t(-m_speed), 0));
		}
	}
}

void Player::mooveTo(int xDestination)
{
	Vector2 position = get_position();

	if (xDestination != position.x) {

		if (xDestination > position.x)
			changeDirection(Direction::RIGHT);
		else
			changeDirection(Direction::LEFT);

		if (xDestination > position.x + NOT_MOOVING_RANGE || xDestination < position.x - NOT_MOOVING_RANGE) {
			m_xDestination = xDestination;
			m_animSprite->set_animation("walk");
			m_animSprite->play();
		}
	}
}

void Player::changeDirection(Direction newDirection)
{
	switch (m_direction)
	{
	case Direction::RIGHT:
		switch (newDirection)
		{
		case Direction::LEFT:
			m_animSprite->set_flip_h(true);
			break;
		default:
			break;
		}
		m_direction = newDirection;
		break;

	case Direction::LEFT:
		switch (newDirection)
		{
		case Direction::RIGHT:
			m_animSprite->set_flip_h(false);
			break;
		default:
			break;
		}
		m_direction = newDirection;
		break;

	default:
		break;
	}
}

void Player::stopMooving()
{
	m_animSprite->set_animation("idle");
	m_animSprite->play();
	m_xDestination = NO_DESTINATION;
}

void Player::setSpeed(int newSpeed)
{
	if (newSpeed < MIN_SPEED)
		m_speed = MIN_SPEED;
	else if (newSpeed > MAX_SPEED)
		m_speed = MAX_SPEED;
	else
		m_speed = newSpeed;
}

int Player::getSpeed()
{
	return m_speed;
}

Direction Player::getDirection()
{
	return m_direction;
}

int Player::getXDestination()
{
	return m_xDestination;
}

Player::Player()
{
	m_animSprite = 0;
	m_direction = Direction::RIGHT;
	m_xDestination = NO_DESTINATION;
	m_speed = MIN_SPEED;
}

Player::~Player()
{
}

void Player::_init()
{
}