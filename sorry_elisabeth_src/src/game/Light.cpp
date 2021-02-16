#include "Light.h"

using namespace godot;

void Light::_register_methods()
{
	register_property<Light, bool>("Visible only when activated", &Light::setOnlyWhenActivated,
		&Light::getOnlyWhenActivated, NULL);
}

void Light::setOnlyWhenActivated(const bool onlyWhenActivated)
{
	m_onlyWhenActivated = onlyWhenActivated;
}

bool Light::getOnlyWhenActivated() const
{
	return m_onlyWhenActivated;
}

Light::Light()
{
	m_onlyWhenActivated = false;
}

Light::~Light()
{
}

void Light::_init()
{
}