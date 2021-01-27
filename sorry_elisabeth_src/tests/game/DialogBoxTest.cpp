#include "DialogBoxTest.h"

using namespace godot;

void DialogBoxTest::_register_methods()
{
	register_method("_ready", &DialogBoxTest::_ready);
}

void DialogBoxTest::_ready()
{
	testIsHided();
}

void DialogBoxTest::testIsHided()
{
	Vector2 testPosition;

	Godot::print("Test with the position.x equal to hidePosition.x");

	Godot::print("Test with the position.y < hidePosition.y");
	testPosition = Vector2(get_position().x, 100);
	set_position(testPosition);
	ASSERT_FALSE(isHided());
	Godot::print("Test passed");

	Godot::print("Test with the position.y > hidePosition.y");
	testPosition = Vector2(get_position().x, Utils::SCREEN_HEIGHT + 200);
	set_position(testPosition);
	ASSERT_FALSE(isHided());
	Godot::print("Test passed");

	Godot::print("Test with the position.y = hidePosition.y");
	set_position(m_hidePosition);
	ASSERT_TRUE(isHided());
	Godot::print("Test passed");


	Godot::print("Test with the position.y equal to hidePosition.y");

	Godot::print("Test with the position.x < hidePosition.x");
	testPosition = Vector2(2, m_hidePosition.y);
	set_position(testPosition);
	ASSERT_FALSE(isHided());
	Godot::print("Test passed");

	Godot::print("Test with the position.x > hidePosition.x");
	testPosition = Vector2(get_position().x + 100, m_hidePosition.y);
	set_position(testPosition);
	ASSERT_FALSE(isHided());
	Godot::print("Test passed");

	Godot::print("Test with the position.x = hidePosition.x");
	set_position(m_hidePosition);
	ASSERT_TRUE(isHided());
	Godot::print("Test passed");
}

DialogBoxTest::DialogBoxTest()
{
}

DialogBoxTest::~DialogBoxTest()
{
}

void DialogBoxTest::_init()
{
}