#include "QuitGameButton.h"

using namespace godot;

void QuitGameButton::_register_methods()
{
	register_method("on_button_down", &QuitGameButton::on_button_down);
}

void QuitGameButton::on_button_down()
{
	get_tree()->quit();	// Quit game
}

void QuitGameButton::_init()
{
	connect("button_down", this, "on_button_down");
}

QuitGameButton::QuitGameButton()
{
}

QuitGameButton::~QuitGameButton()
{
}