#pragma once

#include <Godot.hpp>
#include <TextureButton.hpp>
#include <SceneTree.hpp>
#include <Tree.hpp>

/**
 * Simple button that close the game when pressed down.
 * @version 0.0
 */
class QuitGameButton : public godot::TextureButton {

	GODOT_CLASS(QuitGameButton, godot::TextureButton);	// Needed by godot to be able to use this class

public:

	QuitGameButton();
	~QuitGameButton();

	// Register all methods and properties that godot is directly going to use and call
	static void _register_methods();
	void _init();	// Needed by godot

	/* SIGNALS */
	void on_button_down();	// Quit game
};