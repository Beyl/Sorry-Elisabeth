#include "TakeHangbagInteraction.h"

using namespace godot;

void TakeHandbagInteraction::_register_methods()
{
	register_method("_ready", &TakeHandbagInteraction::_ready);

	register_property<TakeHandbagInteraction, String>("Player's absolute path", &TakeHandbagInteraction::setPlayerAbsolutePath,
		&TakeHandbagInteraction::getPlayerAbsolutePath, "Insert path here");
	register_property<TakeHandbagInteraction, String>("Inventory's absolute path",
		&TakeHandbagInteraction::setInventoryAboslutePath, &TakeHandbagInteraction::getInventoryAboslutePath, "Insert path here");
}

void TakeHandbagInteraction::_ready()
{
	m_inventory = get_node(NodePath(m_inventoryAbsolutePath))->cast_to<Inventory>(get_node(NodePath(m_inventoryAbsolutePath)));
	m_player = get_node(NodePath(m_playerAbsolutePath))->cast_to<Player>(get_node(NodePath(m_playerAbsolutePath)));
}

void TakeHandbagInteraction::play()
{
	m_player->takeHandbag();
	m_inventory->grow();
	get_node(PARENT_INTERACTIVE_OBJECT_PATH)->queue_free();
	ExamineInteraction::play();
}

void TakeHandbagInteraction::setPlayerAbsolutePath(const godot::String newPath)
{
	m_playerAbsolutePath = newPath;
}

godot::String TakeHandbagInteraction::getPlayerAbsolutePath() const
{
	return m_playerAbsolutePath;
}

TakeHandbagInteraction::TakeHandbagInteraction()
{
	m_player = 0;
	m_inventory = 0;

	m_playerAbsolutePath = String();
	m_inventoryAbsolutePath = String();
}

void TakeHandbagInteraction::setInventoryAboslutePath(const godot::String newPath)
{
	m_inventoryAbsolutePath = newPath;
}

godot::String TakeHandbagInteraction::getInventoryAboslutePath() const
{
	return m_inventoryAbsolutePath;
}

TakeHandbagInteraction::~TakeHandbagInteraction()
{
}

void TakeHandbagInteraction::_init()
{
}
