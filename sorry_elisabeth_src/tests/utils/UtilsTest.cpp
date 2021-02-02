#include "UtilsTest.h"

using namespace godot;

void UtilsTest::_init()
{
	runAllTests();
}

void UtilsTest::runAllTests()
{
	testIsInsideRoom();
	testIsInsideRoomX();
	testIsInsideRoomY();
	testGetCenteredPosition();
}

void UtilsTest::testIsInsideRoom()
{
	Vector2 position;

	/* X and Y coordinates > 0*/
	Godot::print("Test for both Y and X contained in the room range");
	position = Vector2(100, 100);
	ASSERT_TRUE(Utils::isInsideRoom(position));

	Godot::print("Test for only the X coordinates contained in the room width range");
	position = Vector2(11, 290);
	ASSERT_FALSE(Utils::isInsideRoom(position));

	Godot::print("Test for only the Y coordinate contained in the room height range");
	position = Vector2(52, 1000);
	ASSERT_FALSE(Utils::isInsideRoom(position));

	Godot::print("Test for both Y and X coordinate not contained in the room range");
	position = Vector2(1000, 909);
	ASSERT_FALSE(Utils::isInsideRoom(position));
	
	/* X and Y coordinates < 0*/
	Godot::print("Test for both Y and X coordinates contained in the room range");
	position = Vector2(100, -17);
	ASSERT_TRUE(Utils::isInsideRoom(position));

	Godot::print("Test for only the X coordinate contained in the room width range");
	position = Vector2(11, -2);
	ASSERT_FALSE(Utils::isInsideRoom(position));

	Godot::print("Test for only the Y coordinate contained in the room height range");
	position = Vector2(52, -505);
	ASSERT_FALSE(Utils::isInsideRoom(position));

	Godot::print("Test for both Y and X coordinates not contained in the room range");
	position = Vector2(-600, -909);
	ASSERT_FALSE(Utils::isInsideRoom(position));

	/* CLOSE TO THE LIMITS */
	Godot::print("Tests for both Y and X coordinates contained in the room range");
	position = Vector2(48, -20);
	ASSERT_TRUE(Utils::isInsideRoom(position));
	position = Vector2(180, 340);
	ASSERT_TRUE(Utils::isInsideRoom(position));

	Godot::print("Tests for only the X coordinate contained in the room width range");
	position = Vector2(47, 18);
	ASSERT_FALSE(Utils::isInsideRoom(position));
	position = Vector2(181, 70);
	ASSERT_FALSE(Utils::isInsideRoom(position));

	Godot::print("Test for only the Y coordinate contained in the room height range");
	position = Vector2(52, -21);
	ASSERT_FALSE(Utils::isInsideRoom(position));
	position = Vector2(52, 341);
	ASSERT_FALSE(Utils::isInsideRoom(position));

	Godot::print("Test for both Y and X coordinates not contained in the room range");
	position = Vector2(47, -21);
	ASSERT_FALSE(Utils::isInsideRoom(position));
	position = Vector2(181, 341);
	ASSERT_FALSE(Utils::isInsideRoom(position));
}

void UtilsTest::testIsInsideRoomX()
{
	real_t xCoord;

	/* X coordinate > 0 */
	Godot::print("Test for X coordinate contained in the room range");
	xCoord = 190;
	ASSERT_TRUE(Utils::isInsideRoomX(xCoord));

	Godot::print("Test for X coordinate not contained in the room range");
	xCoord = 400;
	ASSERT_FALSE(Utils::isInsideRoomX(xCoord));

	/* X coordinate < 0 */
	Godot::print("Test for X coordinate contained in the room range");
	xCoord = -8;
	ASSERT_TRUE(Utils::isInsideRoomX(xCoord));

	Godot::print("Test for X coordinate not contained in the room range");
	xCoord = -54;
	ASSERT_FALSE(Utils::isInsideRoomX(xCoord));

	/* X coordinate close to the limits */
	Godot::print("Tests for X coordinate contained in the room range");
	xCoord = 340;
	ASSERT_TRUE(Utils::isInsideRoomX(xCoord));
	xCoord = -20;
	ASSERT_TRUE(Utils::isInsideRoomX(xCoord));

	Godot::print("Tests for X coordinate not contained in the room range");
	xCoord = -21;
	ASSERT_FALSE(Utils::isInsideRoomX(xCoord));
	xCoord = 341;
	ASSERT_FALSE(Utils::isInsideRoomX(xCoord));
}

void UtilsTest::testIsInsideRoomY()
{
	real_t yCoord;

	Godot::print("Test for Y coordinate contained in the room range");
	yCoord = 81;
	ASSERT_TRUE(Utils::isInsideRoomY(yCoord));

	Godot::print("Tests for Y coordinate not contained in the room range");
	yCoord = 200;
	ASSERT_FALSE(Utils::isInsideRoomY(yCoord));
	yCoord = -71;
	ASSERT_FALSE(Utils::isInsideRoomY(yCoord));
	yCoord = 12;
	ASSERT_FALSE(Utils::isInsideRoomY(yCoord));

	/* Y coordinate close to the limits */
	Godot::print("Tests for Y coordinate contained in the room range");
	yCoord = 180;
	ASSERT_TRUE(Utils::isInsideRoomY(yCoord));
	yCoord = 48;
	ASSERT_TRUE(Utils::isInsideRoomY(yCoord));

	Godot::print("Tests for Y coordinate not contained in the room range");
	yCoord = 47;
	ASSERT_FALSE(Utils::isInsideRoomY(yCoord));
	yCoord = 181;
	ASSERT_FALSE(Utils::isInsideRoomY(yCoord));
}

void UtilsTest::testGetCenteredPosition()
{
	Vector2 testSize, centeredPosition;

	Godot::print("Test with size.x and size.y % 2 = 0");

	Godot::print("Test with a squared object");
	testSize = Vector2(10, 10);
	centeredPosition = Vector2(155, 85);
	ASSERT_EQ(centeredPosition, Utils::getCenteredPosition(testSize));
	Godot::print("Test passed");
	testSize = Vector2(150, 150);
	centeredPosition = Vector2(85, 15);
	ASSERT_EQ(centeredPosition, Utils::getCenteredPosition(testSize));
	Godot::print("Test passed");

	Godot::print("Test with rectangled objects");
	testSize = Vector2(10, 6);
	centeredPosition = Vector2(155, 87);
	ASSERT_EQ(centeredPosition, Utils::getCenteredPosition(testSize));
	Godot::print("Test passed");
	testSize = Vector2(6, 10);
	centeredPosition = Vector2(157, 85);
	ASSERT_EQ(centeredPosition, Utils::getCenteredPosition(testSize));
	Godot::print("Test passed");
	testSize = Vector2(126, 72);
	centeredPosition = Vector2(97, 54);
	ASSERT_EQ(centeredPosition, Utils::getCenteredPosition(testSize));
	Godot::print("Test passed");
	testSize = Vector2(72, 126);
	centeredPosition = Vector2(124, 27);
	ASSERT_EQ(centeredPosition, Utils::getCenteredPosition(testSize));
	Godot::print("Test passed");

	Godot::print("Test with size.x and size.y % 2 = 1");

	Godot::print("Test with a squared object");
	testSize = Vector2(9, 9);
	centeredPosition = Vector2(155, 85);
	ASSERT_EQ(centeredPosition.x, Utils::getCenteredPosition(testSize).x);
	ASSERT_EQ(centeredPosition.y, Utils::getCenteredPosition(testSize).y);
	Godot::print("Test passed");
	testSize = Vector2(172, 172);
	centeredPosition = Vector2(74, 4);
	ASSERT_EQ(centeredPosition.x, Utils::getCenteredPosition(testSize).x);
	ASSERT_EQ(centeredPosition.y, Utils::getCenteredPosition(testSize).y);
	Godot::print("Test passed");

	Godot::print("Test with rectangled objects");
	testSize = Vector2(11, 7);
	centeredPosition = Vector2(154, 86);
	ASSERT_EQ(centeredPosition.x, Utils::getCenteredPosition(testSize).x);
	ASSERT_EQ(centeredPosition.y, Utils::getCenteredPosition(testSize).y);
	Godot::print("Test passed");
	testSize = Vector2(7, 11);
	centeredPosition = Vector2(156, 84);
	ASSERT_EQ(centeredPosition.x, Utils::getCenteredPosition(testSize).x);
	ASSERT_EQ(centeredPosition.y, Utils::getCenteredPosition(testSize).y);
	Godot::print("Test passed");
	testSize = Vector2(149, 115);
	centeredPosition = Vector2(85, 32);
	ASSERT_EQ(centeredPosition.x, Utils::getCenteredPosition(testSize).x);
	ASSERT_EQ(centeredPosition.y, Utils::getCenteredPosition(testSize).y);
	Godot::print("Test passed");
	testSize = Vector2(57, 165);
	centeredPosition = Vector2(131, 7);
	ASSERT_EQ(centeredPosition.x, Utils::getCenteredPosition(testSize).x);
	ASSERT_EQ(centeredPosition.y, Utils::getCenteredPosition(testSize).y);
	Godot::print("Test passed");
}

void UtilsTest::_register_methods()
{
}

UtilsTest::UtilsTest()
{
}

UtilsTest::~UtilsTest()
{
}