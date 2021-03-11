#pragma once

#include <Godot.hpp>
#include <TextureButton.hpp>

#include "SettingsTable.h"
#include "FadeBackground.h"

/**
 * Represents the button that display and hide a settings table.
 * @version beta
 */
class SettingsButton : public godot::TextureButton {

	GODOT_CLASS(SettingsButton, godot::TextureButton);	// Needed by godot to be able to use this class

public:

	SettingsButton();
	~SettingsButton();

	// Register all methods and properties that godot is directly going to use and call
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	// Called every frame. Handle mouse filter when the settings table is displayed
	void _process();


	/* SIGNALS */
	void on_button_down();	// Display the settings table and enable the process method
	void on_settingsTable_just_closed();	// Disable the process method

	void on_mouse_entered();	// Reset the full opacity
	void on_mouse_exited();	// Reduce the opacity

private:

	SettingsTable* m_settingsTable;
	FadeBackground* m_fadeBackground;

	const godot::Color FULL_OPACITY = godot::Color(1, 1, 1, 1);
	const godot::Color QUARTER_OPACITY = godot::Color(1, 1, 1, 0.25);
};