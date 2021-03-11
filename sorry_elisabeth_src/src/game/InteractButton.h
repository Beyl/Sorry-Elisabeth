#pragma once

#include <Godot.hpp>
#include <TextureButton.hpp>
#include <Node2D.hpp>
#include <Tween.hpp>
#include <AnimationPlayer.hpp>
#include <AnimatedSprite.hpp>

/**
 * Represents the button on wich the player has to click to interact with an item or an object.
 * @version beta
 */
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
	bool isDisplayed() const;
	bool isHided() const;

	// Set mouse filter to STOP
	void on_displayAnimation_finished();


	/* PROPERTIES */
	void setHidePosition(const godot::Vector2 newPosition);
	godot::Vector2 getHidePosition() const;

	void setDisplayPosition(const godot::Vector2 newPosition);
	godot::Vector2 getDisplayPosition() const;

	void setAnimationDuration(const real_t newDuration);
	real_t getAnimationDuation() const;


	/* CONSTANTS */
	const int DISPLAY_MARGIN = 1;	// The margin between the parent and the interact button
	const real_t MIN_ANIMATION_DURATION = real_t(0.2);

	const godot::Color NO_OPACITY = godot::Color(1, 1, 1, 0);
	const godot::Color FULL_OPACITY = godot::Color(1, 1, 1, 1);

protected:

	// Children nodes
	godot::Tween* m_tween;

	// Properties
	godot::Vector2 m_hidePosition;
	godot::Vector2 m_displayPosition;
	real_t m_animationDuration;
};