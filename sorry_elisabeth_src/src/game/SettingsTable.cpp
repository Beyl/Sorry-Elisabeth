#include "SettingsTable.h"

using namespace godot;

void SettingsTable::_register_methods()
{
	register_method("_ready", &SettingsTable::_ready);
}

void SettingsTable::_ready()
{
}

SettingsTable::SettingsTable()
{
	m_closeButton = nullptr;
}

SettingsTable::~SettingsTable()
{
}

void SettingsTable::_init()
{
}
