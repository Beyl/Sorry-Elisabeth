#pragma once

#include <Godot.hpp>
#include <ColorRect.hpp>
#include <Tween.hpp>

/**
 * Represents a background that fade in and out to a specific opacity
 */
class FadeBackground : public godot::ColorRect {
	
	GODOT_CLASS(FadeBackground, godot::ColorRect);	//Make godot able to use this class

public:

	FadeBackground();
	~FadeBackground();

	// Register all methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	//Needed by godot;

	// Initialise the godot scene and the class
	void _ready();

	void fadeIn();
	void fadeOut();

	bool isDisplayed();
	

	/* PROPERTIES */

	//The final opacity of the background when it's fully displayed
	float m_displayOpacity;
	void setDisplayOpacity(float newOpacity);
	float getDisplayOpacity();

	real_t m_fadeDuration;
	void setFadeDuration(real_t newDuration);
	real_t getFadeDuration();

protected:

	//Children nodes
	godot::Tween* m_tween;

	godot::Color m_hideColor;
	godot::Color m_displayColor;

	//Constants
	const int MAX_DISPLAY_OPACITY = 1;
	const int MIN_DISPLAY_OPACITY = 0;

	const double MIN_FADE_DURATION = 0.1;
};