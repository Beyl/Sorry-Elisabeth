#include "TakeHangbagInteraction.h"

using namespace godot;

void TakeHandbagInteraction::_register_methods()
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
	m_player = nullptr;
	m_inventory = nullptr;
}

TakeHandbagInteraction::~TakeHandbagInteraction()
{
}

void TakeHandbagInteraction::_init()
{
}
