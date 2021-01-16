#include "PlayerTest.h"

using namespace godot;

void PlayerTest::_register_methods()
{
	register_method("_ready", &PlayerTest::_ready);
}

void PlayerTest::_ready()
{
	runAllTests();
}

void PlayerTest::playerTestInit()
{
	Vector2 playerInitPosition = Vector2(100, 100);
	
	m_player = get_node("Player")->cast_to<Player>(get_node("Player"));
	Godot::print("test2");
	m_player->set_position(playerInitPosition);
}

void PlayerTest::runAllTests()
{
	changeDirectionTest();
}

void PlayerTest::changeDirectionTest()
{
	playerTestInit();
	Direction directionAfterChange;

	Godot::print("Test when the player is looking to the right, then change it's direction to the left");
	directionAfterChange = Direction::LEFT;
	m_player->changeDirection(Direction::LEFT);
	ASSERT_EQ(directionAfterChange, m_player->getDirection());

	Godot::print("Test when the player is looking to the left, then change it's direction to the right");
	directionAfterChange = Direction::RIGHT;
	m_player->changeDirection(Direction::RIGHT);
	ASSERT_EQ(directionAfterChange, m_player->getDirection());

	Godot::print("Test when the player is looking to the right, then change it's direction to the right");
	directionAfterChange = Direction::RIGHT;
	m_player->changeDirection(Direction::RIGHT);
	ASSERT_EQ(directionAfterChange, m_player->getDirection());

	Godot::print("Test when the player is looking to the left, then change it's direction to the left");
	directionAfterChange = Direction::LEFT;
	m_player->changeDirection(Direction::LEFT);
	ASSERT_EQ(directionAfterChange, m_player->getDirection());
}

PlayerTest::PlayerTest()
{
	m_player = 0;
}

PlayerTest::~PlayerTest()
{
}

void PlayerTest::_init()
{
}