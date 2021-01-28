#include "InteractButtonTest.h"

using namespace godot;

void InteractButtonTest::_register_methods()
{
	register_method("_ready", &InteractButtonTest::_ready);
}

void InteractButtonTest::_ready()
{
	testIsDisplayed();
}

void InteractButtonTest::testIsDisplayed()
{
	Color testColor;

	Godot::print("Test with a color that is NOT equal to the display color");
	testColor = Color(float(0.5), 1, -2, float(0.2));
	set_modulate(testColor);
	ASSERT_FALSE(isDisplayed());
	Godot::print("Test passed");

	Godot::print("Test with a color that is equal to the display color, except the opacity");
	testColor = Color(1, 1, 1, float(0.9));
	set_modulate(testColor);
	ASSERT_FALSE(isDisplayed());
	Godot::print("Test passed");

	Godot::print("Test with a color that is NOT equal to the display color, except the opacity");
	testColor = Color(float(0.76), float(0.23), 0, 1);
	set_modulate(testColor);
	ASSERT_FALSE(isDisplayed());
	Godot::print("Test passed");

	Godot::print("Test with a color that is completly equal to the display color");
	testColor = Color(1, 1, 1, 1);
	set_modulate(testColor);
	ASSERT_TRUE(isDisplayed());
	Godot::print("Test passed");
}

InteractButtonTest::InteractButtonTest()
{
}

InteractButtonTest::~InteractButtonTest()
{
}

void InteractButtonTest::_init()
{
}