#pragma once

#include <Godot.hpp>
#include <Light2D.hpp>

class Light : public godot::Light2D {

	GODOT_CLASS(Light, godot::Light2D);

public:

	Light();
	~Light();

	static void _register_methods();
	void _init();	// Needed by godot


	/* PROPERTY */
	void setOnlyWhenActivated(const bool onlyWhenActivated);
	bool getOnlyWhenActivated() const;

private:

	bool m_onlyWhenActivated;	// Enable or not the light when the room light is not activated
};