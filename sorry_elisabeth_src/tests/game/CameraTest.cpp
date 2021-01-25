#include "CameraTest.h"

using namespace godot;

void CameraTest::_register_methods()
{
	register_method("_ready", &CameraTest::_ready);
}

void CameraTest::_ready()
{
	runAllTests();
}

void CameraTest::runAllTests()
{
	isPlayerInsideChangeRoomRangeTest();
	isPlayerEnteringNewRoomTest();
}

void CameraTest::isPlayerInsideChangeRoomRangeTest()
{
	Godot::print("Is player inside change room range tests");

	Godot::print("Test with the player inside the cellar change room range");
	setPlayerPosition(Vector2(LIVING_ROOM_POSITION_X - 5, 0));
	ASSERT_EQ(1, isPlayerInsideChangeRoomRange());

	Godot::print("Test with the player not inside any room range but in the cellar");
	setPlayerPosition(Vector2(100, 0));
	ASSERT_EQ(0, isPlayerInsideChangeRoomRange());

	Godot::print("Test with the player inside the living change room range");
	changeRoom(false);
	setPlayerPosition(Vector2(LIVING_ROOM_POSITION_X + 15, 0));
	ASSERT_EQ(2, isPlayerInsideChangeRoomRange());

	Godot::print("Test with the player not inside any range but in the living room");
	setPlayerPosition(Vector2(500, 0));
	ASSERT_EQ(0, isPlayerInsideChangeRoomRange());
}

void CameraTest::isPlayerEnteringNewRoomTest()
{
	Godot::print("is player entering new room tests");

	//Tests in the cellar
	changeRoom(true);

	Godot::print("Test with the player not inside any range but in the cellar room");
	setPlayerPosition(Vector2(6, 0));
	setPlayerDirection(Direction::RIGHT);
	ASSERT_FALSE(isPlayerEnteringNewRoom());

	Godot::print("Test with the player inside the cellar change room range,");
	Godot::print("but with the wrong direction");
	setPlayerPosition(Vector2(LIVING_ROOM_POSITION_X + 10, 0));
	setPlayerDirection(Direction::LEFT);
	ASSERT_FALSE(isPlayerEnteringNewRoom());

	Godot::print("Test with the player inside the cellar change room range,");
	Godot::print("with the right direction");
	setPlayerPosition(Vector2(LIVING_ROOM_POSITION_X - 5, 0));
	setPlayerDirection(Direction::RIGHT);
	ASSERT_TRUE(isPlayerEnteringNewRoom());

	//Tests in the living room
	changeRoom(false);

	Godot::print("Test with the player not inside any range but in the living room");
	setPlayerPosition(Vector2(406, 0));
	setPlayerDirection(Direction::LEFT);
	ASSERT_FALSE(isPlayerEnteringNewRoom());

	Godot::print("Test with the player inside the living room change room range,");
	Godot::print("but with the wrong direction");
	setPlayerPosition(Vector2(LIVING_ROOM_POSITION_X + 10, 0));
	setPlayerDirection(Direction::RIGHT);
	ASSERT_FALSE(isPlayerEnteringNewRoom());

	Godot::print("Test with the player inside the living room change room range,");
	Godot::print("with the right direction");
	setPlayerPosition(Vector2(LIVING_ROOM_POSITION_X + 5, 0));
	setPlayerDirection(Direction::LEFT);
	ASSERT_TRUE(isPlayerEnteringNewRoom());
}

void CameraTest::_init()
{
}

CameraTest::CameraTest()
{
}

CameraTest::~CameraTest()
{
}