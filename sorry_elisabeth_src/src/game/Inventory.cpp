#include "Inventory.h"

using namespace godot;

void Inventory::_register_methods()
{
	register_method("_ready", &Inventory::_ready);
}

void Inventory::_ready()
{
	// Get children
	m_topInventory = get_node("TopBox")->cast_to<HBoxContainer>(get_node("TopBox"));
	m_bottomInventory = get_node("BottomBox")->cast_to<HBoxContainer>(get_node("BottomBox"));
	m_tween = get_node("Tween")->cast_to<Tween>(get_node("Tween"));

	// Item's array initialisation
	m_itemsNumber = 0;
	for (int i = 0; i < Inventory::MAX_ITEM_NUMBER; i++)
		m_items[i] = 0;

	// Scene initialisation
	//Position initialisation
	const Vector2 parentGlobalPosition = get_parent()->cast_to<TextureButton>(get_parent())->get_global_position();
	m_displayPosition = Utils::getCenteredPosition(get_size()) - parentGlobalPosition;
	m_hidePosition = Vector2(Utils::getCenteredPosition(get_size()).x,
		Utils::SCREEN_HEIGHT + Utils::INVENTORY_HEIGHT) - parentGlobalPosition;
	set_position(m_hidePosition);

	m_currentInventorySize = 5;
	m_bottomInventory->set_position(Vector2(m_bottomInventory->get_position().x,
		Utils::INVENTORY_HEIGHT - m_bottomInventory->get_size().y));
	m_bottomInventory->set_visible(false);
	m_hasGrown = false;
}

void Inventory::display()
{
	set_visible(true);

	m_tween->interpolate_property(this, "rect_position", m_hidePosition, m_displayPosition, ANIMATION_DURATION,
		Tween::TRANS_BACK, Tween::EASE_OUT);
	m_tween->start();
}

void Inventory::hide()
{
	m_tween->interpolate_property(this, "rect_position", m_displayPosition, m_hidePosition, ANIMATION_DURATION,
		Tween::TRANS_BACK, Tween::EASE_IN);
	m_tween->start();
}

void Inventory::addItem(Item* newItem)
{
	if (m_itemsNumber < m_currentInventorySize) {
		m_items[m_itemsNumber] = newItem->duplicate()->cast_to<Item>(newItem->duplicate());
		m_itemsNumber++;
		
		newItem->queue_free();	// Remove the ancient item from the scene (will be added as a child of a cell in the inventory
		updateInventory();
	}
}

void Inventory::removeItem(const Item* itemToDelete)
{
	const int idItem = Inventory::searchItemInArray(m_items, m_itemsNumber, itemToDelete);

	if (idItem > -1) {
		Inventory::removeItemInArray(m_items, m_itemsNumber, idItem);

		updateInventory();
		m_itemsNumber--;
	}
}

void Inventory::updateInventory()
{
	NodePath pathToCell;
	Cell* currentCell = 0;

	for (int i = 0; i < m_itemsNumber; i++) {
		
		const String indexNumber = int(i + int64_t(Utils::ASCII_CONVERSION_0));

		if (i < m_topInventory->get_child_count())
			pathToCell = NodePath("TopBox/Cell" + indexNumber);
		else
			pathToCell = NodePath("BottomBox/Cell" + indexNumber);

		currentCell = get_node(pathToCell)->cast_to<Cell>(get_node(pathToCell));

		if (currentCell->getItem() != m_items[i])
			currentCell->setItem(m_items[i]);
	}
}

void Inventory::grow()
{
	m_bottomInventory->set_visible(true);
	m_hasGrown = true;
	m_currentInventorySize = Inventory::MAX_ITEM_NUMBER;
}

int Inventory::searchItemInArray(Item* itemsArray[], const int arraySize, const Item* pointer)
{
	int id = -1, i = 0;
	bool found = false;

	while (i < arraySize && !found) {
		if (itemsArray[i] == pointer) {
			id = i;
			found = true;
		}
		i++;
	}

	return id;
}

void Inventory::removeItemInArray(Item* itemsArray[], const int arraySize, const int idItem)
{
	for (int i = idItem; i < arraySize; i++) {
		if (i == arraySize - 1)
			itemsArray[i] = 0;
		else {
			if (itemsArray[i + 1] != 0) {
				itemsArray[i] = itemsArray[i + 1]->duplicate()->cast_to<Item>(itemsArray[i + 1]->duplicate());
				itemsArray[i + 1]->queue_free();
			}
			else {
				itemsArray[i] = 0;
				break;
			}
		}
	}
}

Inventory::Inventory()
{
	m_topInventory = 0;
	m_bottomInventory = 0;
	m_tween = 0;
	
	for (int i = 0; i < MAX_ITEM_NUMBER; i++)
		m_items[i] = 0;

	m_itemsNumber = 0;
	m_currentInventorySize = 0;
	m_hasGrown = false;
	m_hidePosition = Vector2();
	m_displayPosition = Vector2();
}

Inventory::~Inventory()
{
}

void Inventory::_init()
{
}