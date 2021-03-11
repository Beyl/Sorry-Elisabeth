#pragma once

#include "Panel.h"

/**
 * Represents a panel containing various settings options (quit game / sound settings / subtitles...)
 * @version beta
 */
class SettingsTable : public Panel {

	GODOT_SUBCLASS(SettingsTable, Panel);	// Needed by godot to be able to use this class

public:

	SettingsTable();
	~SettingsTable();

	// Register all methods and properties that godot is directly going to use and call
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

private:

	godot::TextureButton* m_closeButton;
};