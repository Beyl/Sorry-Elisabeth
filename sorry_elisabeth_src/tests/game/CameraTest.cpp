#include "CameraTest.h"

using namespace godot;

void CameraTest::_register_methods()
{
	register_method("_ready", &CameraTest::_ready);
}

void CameraTest::_ready()
{
	m_camera = get_node("Camera")->cast_to<Camera>(get_node("Camera"));
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
	m_camera->setPlayerPosition(Vector2(Utils::LIVING_ROOM_POSITION_X - 5, 0));
	ASSERT_EQ(1, m_camera->isPlayerInsideChangeRoomRange());

	Godot::print("Test with the player not inside any room range but in the cellar");
	m_camera->setPlayerPosition(Vector2(100, 0));
	ASSERT_EQ(0, m_camera->isPlayerInsideChangeRoomRange());

	Godot::print("Test with the player inside the living change room range");
	m_camera->changeRoom(false);
	m_camera->setPlayerPosition(Vector2(Utils::LIVING_ROOM_POSITION_X + 15, 0));
	ASSERT_EQ(2, m_camera->isPlayerInsideChangeRoomRange());

	Godot::print("Test with the player not inside any range but in the living room");
	m_camera->setPlayerPosition(Vector2(500, 0));
	ASSERT_EQ(0, m_camera->isPlayerInsideChangeRoomRange());
}

void CameraTest::isPlayerEnteringNewRoomTest()
{
	Godot::print("is player entering new room tests");

	//Tests in the cellar
	m_camera->changeRoom(true);

	Godot::print("Test with the player not inside any range but in the cellar room");
	m_camera->setPlayerPosition(Vector2(6, 0));
	m_camera->setPlayerDirection(Direction::RIGHT);
	ASSERT_FALSE(m_camera->isPlayerEnteringNewRoom());

	Godot::print("Test with the player inside the cellar change room range,");
	Godot::print("but with the wrong direction");
	m_camera->setPlayerPosition(Vector2(Utils::LIVING_ROOM_POSITION_X + 10, 0));
	m_camera->setPlayerDirection(Direction::LEFT);
	ASSERT_FALSE(m_camera->isPlayerEnteringNewRoom());

	Godot::print("Test with the player inside the cellar change room range,");
	Godot::print("with the right direction");
	m_camera->setPlayerPosition(Vector2(Utils::LIVING_ROOM_POSITION_X - 5, 0));
	m_camera->setPlayerDirection(Direction::RIGHT);
	ASSERT_TRUE(m_camera->isPlayerEnteringNewRoom());

	//Tests in the living room
	m_camera->changeRoom(false);

	Godot::print("Test with the player not inside any range but in the living room");
	m_camera->setPlayerPosition(Vector2(406, 0));
	m_camera->setPlayerDirection(Direction::LEFT);
	ASSERT_FALSE(m_camera->isPlayerEnteringNewRoom());

	Godot::print("Test with the player inside the living room change room range,");
	Godot::print("but with the wrong direction");
	m_camera->setPlayerPosition(Vector2(Utils::LIVING_ROOM_POSITION_X + 10, 0));
	m_camera->setPlayerDirection(Direction::RIGHT);
	ASSERT_FALSE(m_camera->isPlayerEnteringNewRoom());

	Godot::print("Test with the player inside the living room change room range,");
	Godot::print("with the right direction");
	m_camera->setPlayerPosition(Vector2(Utils::LIVING_ROOM_POSITION_X + 5, 0));
	m_camera->setPlayerDirection(Direction::LEFT);
	ASSERT_TRUE(m_camera->isPlayerEnteringNewRoom());
}

void CameraTest::_init()
{
}

CameraTest::CameraTest()
{
	m_camera = 0;
}

CameraTest::~CameraTest()
{
}