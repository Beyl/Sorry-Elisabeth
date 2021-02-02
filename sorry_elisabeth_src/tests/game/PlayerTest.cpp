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
	
	Godot::print("test2");
	set_position(playerInitPosition);
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
	changeDirection(Direction::LEFT);
	ASSERT_EQ(directionAfterChange, getDirection());
	Godot::print("Test passed");

	Godot::print("Test when the player is looking to the left, then change it's direction to the right");
	directionAfterChange = Direction::RIGHT;
	changeDirection(Direction::RIGHT);
	ASSERT_EQ(directionAfterChange, getDirection());
	Godot::print("Test passed");

	Godot::print("Test when the player is looking to the right, then change it's direction to the right");
	directionAfterChange = Direction::RIGHT;
	changeDirection(Direction::RIGHT);
	ASSERT_EQ(directionAfterChange, getDirection());
	Godot::print("Test passed");

	Godot::print("Test when the player is looking to the left, then change it's direction to the left");
	directionAfterChange = Direction::LEFT;
	changeDirection(Direction::LEFT);
	ASSERT_EQ(directionAfterChange, getDirection());
	Godot::print("Test passed");
}

PlayerTest::PlayerTest()
{
}

PlayerTest::~PlayerTest()
{
}

void PlayerTest::_init()
{
}