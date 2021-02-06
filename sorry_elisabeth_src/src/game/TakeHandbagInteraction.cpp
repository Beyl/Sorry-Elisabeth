#include "TakeHangbagInteraction.h"

using namespace godot;

void TakeHandbagInteraction::_register_methods()
{
}

void TakeHandbagInteraction::_init()
{
}

void TakeHandbagInteraction::play()
{
	m_player->takeHandbag();
	m_inventory->grow();
	get_node(PARENT_INTERACTIVE_OBJECT_PATH)->queue_free();
	ExamineInteraction::play();
}

void TakeHandbagInteraction::setPlayer(Player* newPlayer)
{
	m_player = newPlayer;
}

void TakeHandbagInteraction::setInventory(Inventory* newInventory)
{
	m_inventory = newInventory;
}

TakeHandbagInteraction::TakeHandbagInteraction()
{
	m_player = 0;
	m_inventory = 0;
}

TakeHandbagInteraction::~TakeHandbagInteraction()
{
}