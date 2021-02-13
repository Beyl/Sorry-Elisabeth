#include "Inventory.h"

using namespace godot;

void Inventory::_register_methods()
{
	register_method("_ready", &Inventory::_ready);
	register_method("on_cellsButtonInSpecialMode_clicked", &Inventory::on_cellsButtonInSpecialMode_clicked);
	register_method("on_hideAnimation_completed", &Inventory::on_hideAnimation_completed);
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
	m_specialMode = false;
	m_combineInteraction = nullptr;
	m_useInteraction = nullptr;
	//Position initialisation
	const Vector2 parentGlobalPosition = get_parent()->cast_to<TextureButton>(get_parent())->get_global_position();
	m_displayPosition = Utils::getCenteredPosition(get_size()) - parentGlobalPosition;
	m_hidePosition = Vector2(Utils::getCenteredPosition(get_size()).x,
		Utils::SCREEN_HEIGHT + Utils::INVENTORY_HEIGHT) - parentGlobalPosition;
	set_position(m_hidePosition);

	m_currentInventorySize = Inventory::MIN_ITEM_NUMBER;
	m_bottomInventory->set_position(Vector2(m_bottomInventory->get_position().x,
		Utils::INVENTORY_HEIGHT - m_bottomInventory->get_size().y));
	m_bottomInventory->set_visible(false);
	m_hasGrown = false;

	// Signal initialisation
	add_user_signal("interact");
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
	m_tween->connect("tween_all_completed", this, "on_hideAnimation_completed");

	m_tween->interpolate_property(this, "rect_position", m_displayPosition, m_hidePosition, ANIMATION_DURATION,
		Tween::TRANS_BACK, Tween::EASE_IN);
	m_tween->start();
}

Cell* Inventory::getCellWithNumber(const int cellNumber) const
{
	Cell* cell = nullptr;

	if (cellNumber >= 0 && cellNumber < Inventory::MAX_ITEM_NUMBER) {
		NodePath pathToCell;
		const String stringCellNumber = int(cellNumber + int64_t(Utils::ASCII_CONVERSION_0));

		if (cellNumber < m_topInventory->get_child_count())
			pathToCell = NodePath("TopBox/Cell" + stringCellNumber);
		else
			pathToCell = NodePath("BottomBox/Cell" + stringCellNumber);

		cell = get_node(pathToCell)->cast_to<Cell>(get_node(pathToCell));
	}

	return cell;
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
			if (itemsArray[i + 1] != nullptr) {
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

void Inventory::addItem(Item* newItem)
{
	if (m_itemsNumber < m_currentInventorySize) {
		m_items[m_itemsNumber] = newItem->duplicate()->cast_to<Item>(newItem->duplicate());
		m_itemsNumber++;
		
		newItem->queue_free();	// Remove the ancient item from the scene (will be added as a child of a cell in the inventory
		updateInventory();
		emit_signal("interact");
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

void Inventory::removeItemByName(const godot::String itemName)
{
	Cell* currentCell = nullptr;
	for (int i = 0; i < m_itemsNumber; i++) {

		currentCell = getCellWithNumber(i);

		if (currentCell->getItem()->get_name() == itemName)
			removeItem(currentCell->getItem());
	}
}

void Inventory::updateInventory()
{
	Cell* currentCell = nullptr;

	for (int i = 0; i < m_itemsNumber; i++) {
		
		currentCell = getCellWithNumber(i);

		if (currentCell->getItem() != m_items[i])
			currentCell->setItem(m_items[i]);
	}
}

void Inventory::setCellsInSpecialMode()
{
	Cell* currentCell = nullptr;

	for (int i = 0; i < m_itemsNumber; i++) {

		currentCell = getCellWithNumber(i);

		if (currentCell->getItem() != nullptr) {
			currentCell->enableSpecialMode();
			currentCell->connect("clicked", this, "on_cellsButtonInSpecialMode_clicked");
		}
	}
}

void Inventory::disableSpecialMode()
{
	Cell* currentCell = nullptr;

	for (int i = 0; i < m_itemsNumber; i++) {

		currentCell = getCellWithNumber(i);

		if (currentCell->getItem() != nullptr) {
			currentCell->disableUseMode();
			currentCell->disconnect("clicked", this, "on_cellsButtonInSpecialMode_clicked");
		}
	}

	m_specialMode = 0;
	m_useInteraction = nullptr;
	m_combineInteraction = nullptr;
}

void Inventory::enableSpecialMode(Interaction* specialInteraction)
{
	if (specialInteraction->get_name().find("UseInteraction") != -1) {
		m_useInteraction = specialInteraction->cast_to<UseInteraction>(specialInteraction);
		m_specialMode = 1;
	}
	else {
		m_combineInteraction = specialInteraction->cast_to<CombineInteraction>(specialInteraction);
		m_specialMode = 2;
	}
	setCellsInSpecialMode();
}

void Inventory::use(Cell* itemsCellToUse)
{
	InteractiveObject* useInteractionObject =
		m_useInteraction->get_node(m_useInteraction->PARENT_INTERACTIVE_OBJECT_PATH)->cast_to<InteractiveObject>
		(m_useInteraction->get_node(m_useInteraction->PARENT_INTERACTIVE_OBJECT_PATH));

	if (itemsCellToUse->getItem()->get_name() == useInteractionObject->getUseItemName()) {
		m_useInteraction->playSucceededExamination();
		useInteractionObject->increaseState(m_useInteraction->getNextInteractions(), m_useInteraction);
		get_parent()->cast_to<InventoryButton>(get_parent())->on_button_released();
	}
	else
		m_useInteraction->playFailedExamination();
}

void Inventory::combine(Cell* itemsCellToCombine)
{
	Item* cellToCombineItem = itemsCellToCombine->getItem();
	String name = cellToCombineItem->get_name();

	// If the name corresponds, add the new item and remove the two parents.
	if (m_combineInteraction->getCombinedItems().has(name)) {
		Ref<PackedScene> combinedItemScene = m_combineInteraction->getCombinedItems()[name];
		addItem(combinedItemScene->instance()->cast_to<Item>(combinedItemScene->instance()));

		m_combineInteraction->playSucceededExamination();

		Item* combineInteractionItem =
			m_combineInteraction->get_node(m_combineInteraction->PARENT_INTERACTIVE_OBJECT_PATH)->cast_to<Item>
			(m_combineInteraction->get_node(m_combineInteraction->PARENT_INTERACTIVE_OBJECT_PATH));
		removeItem(combineInteractionItem);
		removeItemByName(name);

		disableSpecialMode();
	}
	else {
		m_combineInteraction->playFailedExamination();
		disableSpecialMode();
	}
}

void Inventory::on_cellsButtonInSpecialMode_clicked(Cell* itemsCellToInteract)
{
	if (m_specialMode == 1)
		use(itemsCellToInteract);
	else
		combine(itemsCellToInteract);
	
}

void Inventory::on_hideAnimation_completed()
{
	if (m_specialMode != 0)
		disableSpecialMode();

	m_tween->disconnect("tween_all_completed", this, "on_hideAnimation_completed");
}

void Inventory::grow()
{
	m_bottomInventory->set_visible(true);
	m_hasGrown = true;
	m_currentInventorySize = Inventory::MAX_ITEM_NUMBER;
	emit_signal("interact");
}

Inventory::Inventory()
{
	m_topInventory = nullptr;
	m_bottomInventory = nullptr;
	m_tween = nullptr;
	
	for (int i = 0; i < MAX_ITEM_NUMBER; i++)
		m_items[i] = nullptr;

	m_itemsNumber = 0;
	m_currentInventorySize = 0;
	m_hasGrown = false;

	m_specialMode = 0;
	m_useInteraction = nullptr;
	m_combineInteraction = nullptr;

	m_hidePosition = Vector2();
	m_displayPosition = Vector2();
}

Inventory::~Inventory()
{
}

void Inventory::_init()
{
}
