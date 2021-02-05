#pragma once

#include <Godot.hpp>
#include <ColorRect.hpp>
#include <Tween.hpp>

#include "../utils/Utils.h"

/**
 * Represents a background that fade in and out to a specific opacity
 */
class FadeBackground : public godot::ColorRect {
	
	GODOT_CLASS(FadeBackground, godot::ColorRect);	// Needed by godot to be able to use this class

public:

	FadeBackground();
	~FadeBackground();

	// Register all methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	// Needed by godot;

	// Initialise the godot scene and the class
	void _ready();

	void fadeIn();
	void fadeOut();

	bool isDisplayed() const;
	bool isHided() const;

	
	/* SIGNALS */

	// Emit the signal associated
	void on_fadeIn_finished();

	// Emit the signal associated
	void on_fadeOut_finished();


	/* PROPERTIES */
	void setDisplayOpacity(const float newOpacity);
	float getDisplayOpacity() const;

	void setFadeDuration(const real_t newDuration);
	real_t getFadeDuration() const;


	/* CONSTANTS */
	const int MAX_DISPLAY_OPACITY = 1;
	const int MIN_DISPLAY_OPACITY = 0;
	const double MIN_FADE_DURATION = 0.1;
	const godot::Color HIDE_COLOR = godot::Color(0, 0, 0, 0);

protected:

	//Child node
	godot::Tween* m_tween;

	godot::Color m_displayColor;

	// Properties
	float m_displayOpacity;	// The final opacity of the background when it's fully displayed
	real_t m_fadeDuration;
};