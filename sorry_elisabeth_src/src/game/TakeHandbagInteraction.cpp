#include "TakeHangbagInteraction.h"

using namespace godot;

void TakeHandbagInteraction::_register_methods()
{
	register_method("on_examineInteraction_finished", &TakeHandbagInteraction::on_examineInteraction_finished);
}

void TakeHandbagInteraction::play()
{
	m_player->takeHandbag();
	m_inventory->grow();
	get_node(PARENT_INTERACTIVE_OBJECT_PATH)->cast_to<Node2D>(get_node(PARENT_INTERACTIVE_OBJECT_PATH))->set_visible(false);
	ExamineInteraction::play();
	ExamineInteraction::connect("interaction_finished", this, "on_examineInteraction_finished");
}

void TakeHandbagInteraction::on_examineInteraction_finished()
{
	get_node(PARENT_INTERACTIVE_OBJECT_PATH)->cast_to<Node2D>(get_node(PARENT_INTERACTIVE_OBJECT_PATH))->queue_free();
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
