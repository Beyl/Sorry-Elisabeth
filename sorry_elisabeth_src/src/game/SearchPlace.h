#pragma once

#include <Godot.hpp>
#include <TextureRect.hpp>
#include <Tween.hpp>
#include <TextureButton.hpp>
#include <StreamTexture.hpp>

#include "../utils/Utils.h"

/**
 * Represents the content of an open interaction.
 		Contain OR NOT a list of inventory items
 */
class SearchPlace : public godot::TextureRect {

	GODOT_CLASS(SearchPlace, godot::TextureRect);	// Needed by godot to be able to use this class

public:

	SearchPlace();
	~SearchPlace();
	
	//  Register all methods and properties that godot is directyl going to call or use
	static void _register_methods();
	void _init(); // Needed by godot
	
	// Initialise the class and the godot scene
	void _ready();
	
	void display();
	void hide();

	// Hide the search place
	void on_closeButton_released();


	/* ACCESSORS */
	real_t getAnimationDuration() const;
	godot::TextureButton* getCloseButton() const;

protected:

	//Children nodes
	godot::Tween* m_tween;
	godot::TextureButton* m_closeButton;

	godot::Vector2 m_displayPosition;
	godot::Vector2 m_hidingPosition;
	const real_t TWEEN_ANIMATION_DURATION = real_t(0.5);
};