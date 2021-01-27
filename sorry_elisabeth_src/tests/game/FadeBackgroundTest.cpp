#include "FadeBackgroundTest.h"

using namespace godot;

void FadeBackgroundTest::_register_methods()
{
	register_method("_ready", &FadeBackgroundTest::_ready);
}

void FadeBackgroundTest::_ready()
{
	testIsDisplayed();
}

void FadeBackgroundTest::testIsDisplayed()
{
	Color testColor;
	setDisplayOpacity(1);
	m_displayColor = Color(0, 0, 0, m_displayOpacity);

	Godot::print("Test with a color that is NOT equal to the display color");
	testColor = Color(float(0.5), 1, -2, float(0.2));
	set_frame_color(testColor);
	ASSERT_FALSE(isDisplayed());
	Godot::print("Test passed");

	Godot::print("Test with a color that is equal to the display color, except the opacity");
	testColor = Color(0, 0, 0, float(0.9));
	set_frame_color(testColor);
	ASSERT_FALSE(isDisplayed());
	Godot::print("Test passed");

	Godot::print("Test with a color that is NOT equal to the display color, except the opacity");
	testColor = Color(float(0.76), float(0.23), 0, 1);
	set_frame_color(testColor);
	ASSERT_FALSE(isDisplayed());
	Godot::print("Test passed");

	Godot::print("Test with a color that is completly equal to the display color");
	testColor = Color(0, 0, 0, 1);
	set_frame_color(testColor);
	ASSERT_TRUE(isDisplayed());
	Godot::print("Test passed");
}

FadeBackgroundTest::FadeBackgroundTest()
{
}

FadeBackgroundTest::~FadeBackgroundTest()
{
}

void FadeBackgroundTest::_init()
{
}