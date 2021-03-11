#pragma once

#include <Godot.hpp>
#include <TextureRect.hpp>
#include <Tween.hpp>
#include <TextureButton.hpp>
#include <StreamTexture.hpp>

#include "../utils/Utils.h"

/**
 * Represents a panel / window that can be displayed on the screen and hided with a smooth animation
 * @version 0.0
 */
class Panel : public godot::TextureRect {

	GODOT_CLASS(Panel, godot::TextureRect);	// Needed by godot to be able to use this class

public:

	Panel();
	~Panel();

	//  Register all methods and properties that godot is directyl going to call or use
	static void _register_methods();
	void _init(); // Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	void display();
	void hide();
	bool isHided() const;

	/* SIGNALS */
	void on_closeButton_released();	// Hide the panel


	/* ACCESSORS */
	real_t getAnimationDuration() const;


	/* CONSTANTS */
	const real_t ANIMATION_DURATION = real_t(0.5);

protected:

	//Children nodes
	godot::Tween* m_tween;
	godot::TextureButton* m_closeButton;

	godot::Vector2 m_displayPosition;
	godot::Vector2 m_hidingPosition;
};