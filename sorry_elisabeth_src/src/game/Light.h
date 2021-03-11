#pragma once

#include <Godot.hpp>
#include <Light2D.hpp>

/**
 * Represents a simple light in a room that contains the needed information to execute the "active light" interaction.
 * @version 0.0
 */
class Light : public godot::Light2D {

	GODOT_CLASS(Light, godot::Light2D);	// Needed by godot to be able to use this class

public:

	Light();
	~Light();

	static void _register_methods();	// Register all methods, signals and properties that godot is directly going to call
	void _init();	// Needed by godot


	/* PROPERTY */
	void setOnlyWhenActivated(const bool onlyWhenActivated);
	bool getOnlyWhenActivated() const;

private:

	bool m_onlyWhenActivated;	// Enable or not the light when the room light is not activated
};