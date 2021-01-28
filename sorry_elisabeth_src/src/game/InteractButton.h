#pragma once

#include <Godot.hpp>
#include <TextureButton.hpp>
#include <Node2D.hpp>
#include <Tween.hpp>
#include <AnimationPlayer.hpp>
#include <AnimatedSprite.hpp>

class InteractButton : public godot::TextureButton {

	GODOT_CLASS(InteractButton, godot::TextureButton);	// Needed by godot to be able to use this class

public:

	InteractButton();
	~InteractButton();

	// Register all the methods and properties that godot is directly going to use and call
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	void display();
	void hide();
	bool isDisplayed();


	/* PROPERTIES */

	godot::Vector2 m_hidePosition;
	void setHidePosition(godot::Vector2 newPosition);
	godot::Vector2 getHidePosition();

	godot::Vector2 m_displayPosition;
	void setDisplayPosition(godot::Vector2 newPosition);
	godot::Vector2 getDisplayPosition();

	real_t m_animationDuration;
	void setAnimationDuration(real_t newDuration);
	real_t getAnimationDuation();


	/* CONSTANTS */

	const int DISPLAY_MARGIN = 1;	// The margin between the parent and the interact button
	const real_t MIN_ANIMATION_DURATION = real_t(0.2);

	const godot::Color NO_OPACITY = godot::Color(1, 1, 1, 0);
	const godot::Color FULL_OPACITY = godot::Color(1, 1, 1, 1);

	const godot::Vector2 NORMAL_SCALE = godot::Vector2(1, 1);
	const godot::Vector2 INVERT_SCALE = godot::Vector2(-1, 1);

protected:

	// Children nodes
	godot::Tween* m_tween;
	godot::AnimationPlayer* m_animationPlayer;
};