#include "TakeInteraction.h"

using namespace godot;

void TakeInteraction::_register_methods()
{
	register_method("_ready", &TakeInteraction::_ready);
	register_method("on_examineInteraction_finished", &TakeInteraction::on_examineInteraction_finished);

	register_property<TakeInteraction, Ref<PackedScene>>("Item", &TakeInteraction::setItemScene,
		&TakeInteraction::getItemScene, Ref<PackedScene>());
	register_property<TakeInteraction, String>("Item name", &TakeInteraction::setItemSceneName,
		&TakeInteraction::getItemSceneName, "Insert item name");
}

void TakeInteraction::_ready()
{
	m_parentInteractiveObject = get_node(PARENT_INTERACTIVE_OBJECT_PATH)->cast_to<InteractiveObject>
		(get_node(PARENT_INTERACTIVE_OBJECT_PATH));

	connect("interaction_finished", this, "on_examineInteraction_finished");
}

void TakeInteraction::play()
{
	// Add the item to the inventory
	add_child(m_itemScene->instance());
	m_inventory->addItem(get_node(NodePath(m_itemSceneName))->cast_to<Item>(get_node(NodePath(m_itemSceneName))));

	// Play the examine interaction wich goes with it
	ExamineInteraction::play();
	
	// Hide the parent before deleting it when the examine interaction is finished
	m_parentInteractiveObject->set_visible(false);
}

void TakeInteraction::on_examineInteraction_finished()
{
	m_parentInteractiveObject->queue_free();
}

void TakeInteraction::setInventory(Inventory* newInventory)
{
	m_inventory = newInventory;
}

void TakeInteraction::setItemScene(const godot::Ref<godot::PackedScene> newItemScene)
{
	m_itemScene = newItemScene;
}

godot::Ref<godot::PackedScene> TakeInteraction::getItemScene() const
{
	return m_itemScene;
}

void TakeInteraction::setItemSceneName(const godot::String newName)
{
	m_itemSceneName = newName;
}

godot::String TakeInteraction::getItemSceneName() const
{
	return m_itemSceneName;
}

TakeInteraction::TakeInteraction()
{
	m_inventory = 0;
	m_parentInteractiveObject = 0;
	m_itemScene = Ref<PackedScene>();
}

TakeInteraction::~TakeInteraction()
{
}

void TakeInteraction::_init()
{
}