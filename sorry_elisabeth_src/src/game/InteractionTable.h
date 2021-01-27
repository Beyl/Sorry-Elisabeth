#pragma once

#include <Godot.hpp>
#include <TextureRect.hpp>
#include <VBoxContainer.hpp>
#include <Tween.hpp>

/**
 * Contain 1 to 3 interactions wich the player can interact with.
 *		The size of the table fits with the number of interactions inside.
 */
class InteractionTable : public godot::TextureRect {

	GODOT_CLASS(InteractionTable, godot::TextureRect);	//Needed by godot to be able to use this class

public:

	InteractionTable();
	~InteractionTable();
	
	// Register all methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init(); //Needed by godot
	
	// Initialise of the class and the godot scene
	void _ready();

	void display();	//Use the tween to animate the table display
	void hide();	//Use the tween to animate the table hiding

protected:

	//Children nodes
	godot::VBoxContainer* m_vBox;
	godot::Tween* m_tween;

	real_t m_animationDuration;

	const real_t MIN_VBOX_SIZE = 12;
	const real_t VBOX_MARGIN = 2;
	const godot::Vector2 NO_SCALE = godot::Vector2(0, 0);
	const godot::Vector2 FULL_SCALE = godot::Vector2(1, 1);
	const godot::Color HIDE_MODULATE = godot::Color(1, 1, 1, 0);
	const godot::Color DISPLAY_MODULATE = godot::Color(1, 1, 1, 1);
};