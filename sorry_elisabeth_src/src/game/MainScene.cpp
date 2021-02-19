#include "MainScene.h"

#include "TakeHangbagInteraction.h"
#include "TakeInteraction.h"
#include "OpenDoorInteraction.h"
#include "OpenInteraction.h"
#include "ActiveLightInteraction.h"

using namespace godot;

void MainScene::_register_methods()
{
	register_method("_ready", &MainScene::_ready);
	register_method("_physics_process", &MainScene::_physics_process);
	register_method("on_inventory_item_added", &MainScene::on_inventory_item_added);
	register_method("on_room1_door_opened", &MainScene::on_room1_door_opened);
	register_method("on_room_interaction_just_played", &MainScene::on_room_interaction_just_played);
	register_method("on_room_interaction_finished", &MainScene::on_room_interaction_finished);
	register_method("on_openInteraction_just_played", &MainScene::on_openInteraction_just_played);
	register_method("on_openInteraction_finished", &MainScene::on_openInteraction_finished);
	register_method("on_mouse_entered_button", &MainScene::on_mouse_entered_button);
	register_method("on_mouse_exited_button", &MainScene::on_mouse_exited_button);
	register_method("on_dialogBox_just_started", &MainScene::on_dialogBox_just_started);
	register_method("on_dialogBox_just_hided", &MainScene::on_dialogBox_just_hided);
}

void MainScene::_ready()
{
	// Member variables initialisation
	m_inputManager = Input::get_singleton();
	m_playerIsInteracting = false;
	m_inOpenInteraction = false;
	m_mouseIsInButton = false;

	// Get the children
	m_player = get_node("Player")->cast_to<Player>(get_node("Player"));
	m_camera = get_node("Camera")->cast_to<Camera>(get_node("Camera"));
	m_inventory = get_node("UILayer/InventoryButton/Inventory")->cast_to<Inventory>
		(get_node("UILayer/InventoryButton/Inventory"));
	m_room1 = get_node("Room1")->cast_to<Room>(get_node("Room1"));
	m_room2 = get_node("Room2")->cast_to<Room>(get_node("Room2"));

	// Scene initialisation
	m_player->setMaxPositionRight(Utils::SCREEN_WIDTH - Player::SPRITE_WIDTH / 2);
	m_player->set_position(Vector2(real_t(PLAYER_START_X), real_t(PLAYER_START_Y)));

	m_camera->setEnableChangeRoom(false);
	sendInfoToInteractions(this);

	m_room1->setPlayer(m_player);
	m_room2->setPlayer(m_player);

	m_room1->setLightIsOn(false);

	// Signals initialisation
	connectNeededSignals(this);
	m_inventory->connect("item_added", this, "on_inventory_item_added");
	m_room1->connect("door_opened", this, "on_room1_door_opened");
	m_room1->connect("interaction_just_played", this, "on_room_interaction_just_played");
	m_room1->connect("interaction_finished", this, "on_room_interaction_finished");
	m_room2->connect("interaction_just_played", this, "on_room_interaction_just_played");
	m_room2->connect("interaction_finished", this, "on_room_interaction_finished");
}

void MainScene::_physics_process()
{
	if (!m_inventory->isOpen()) {

		if (m_inputManager->is_action_just_released("mouse_left_click")) {
			if (canPlayerMoove()) {
				// If a left click is done, moove the player to the this point
				m_player->mooveTo(int(get_local_mouse_position().x));
			}
		}
	}
	else
		m_inventory->manageInteractions();

	sendPlayerInfoToCam();
	m_room1->setInventoryIsOpen(m_inventory->isOpen());
	m_room1->manageInteractions();
}

void MainScene::on_inventory_item_added()
{
	connectNeededSignals(m_inventory);
}

void MainScene::on_room1_door_opened()
{
	m_camera->setEnableChangeRoom(true);
	m_player->setMaxPositionRight(Utils::SCREEN_WIDTH * 2 - Player::SPRITE_WIDTH / 2);
}

void MainScene::sendPlayerInfoToCam()
{
	m_camera->setPlayerPosition(m_player->get_position());
	m_camera->setPlayerDirection(m_player->getDirection());
}

void MainScene::sendInfoToInteractions(Node* currentNode)
{
	bool hasBeenSet = false;

	if (currentNode->get_name().find(TAKE_HANDBAG_INTERACTION_NODE_NAME) != -1) {
		currentNode->cast_to<TakeHandbagInteraction>(currentNode)->setPlayer(m_player);
		currentNode->cast_to<TakeHandbagInteraction>(currentNode)->setInventory(m_inventory);
		hasBeenSet = true;
	}
	else if (currentNode->get_name().find(TAKE_INTERACTION_NODE_NAME) != -1) {
		currentNode->cast_to<TakeInteraction>(currentNode)->setInventory(m_inventory);
		hasBeenSet = true;
	}
	else if (currentNode->get_name().find(USE_INTERACTION_NODE_NAME) != -1) {
		currentNode->cast_to<UseInteraction>(currentNode)->setInventory(m_inventory);
		hasBeenSet = true;
	}
	else if (currentNode->get_name().find(COMBINE_INTERACTION_NODE_NAME) != -1) {
		currentNode->cast_to<CombineInteraction>(currentNode)->setInventory(m_inventory);
		hasBeenSet = true;
	}
	else if (currentNode->get_name().find(OPEN_DOOR_INTERACTION_NODE_NAME) != -1) {
		currentNode->cast_to<OpenDoorInteraction>(currentNode)->setRoom(m_room1);
		hasBeenSet = true;
	} else if (currentNode->get_name().find(ACTIVE_LIGHT_R1_INTERACTION_NODE_NAME) != -1) {
		currentNode->cast_to<ActiveLightInteraction>(currentNode)->setRoom(m_room1);
		hasBeenSet = true;
	} else if (currentNode->get_name().find(ACTIVE_LIGHT_R2_INTERACTION_NODE_NAME) != -1) {
		currentNode->cast_to<ActiveLightInteraction>(currentNode)->setRoom(m_room2);
		hasBeenSet = true;
	}

	if (!hasBeenSet) {
		for (int i = 0; i < currentNode->get_child_count(); i++)
			sendInfoToInteractions(currentNode->get_child(i));
	}
}

void MainScene::connectNeededSignals(Node* currentNode)
{
	bool continueConnecting = true;

	if (currentNode->get_name().find("Interaction") != -1 ||
		currentNode->get_name().find(INTERACT_BUTTON_NODE_NAME) != -1 ||
		currentNode->get_name().find(INVENTORY_BUTTON_NODE_NAME) != -1 ||
		currentNode->get_name().find(CLOSE_BUTTON_NODE_NAME) != -1) {

		currentNode->cast_to<Control>(currentNode)->connect("mouse_entered", this, "on_mouse_entered_button");
		currentNode->cast_to<Control>(currentNode)->connect("mouse_exited", this, "on_mouse_exited_button");

		if (currentNode->get_name().find(OPEN_INTERACTION_NODE_NAME) != -1) {
			currentNode->cast_to<OpenInteraction>(currentNode)->
				connect("openInteraction_just_played", this, "on_openInteraction_just_played");
			currentNode->cast_to<OpenInteraction>(currentNode)->
				connect("openInteraction_finished", this, "on_openInteraction_finished");

			continueConnecting = false;
		}
	}
	else if (currentNode->get_name() == DIALOGBOX_NODE_NAME) {

		if (currentNode->get_parent()->get_parent()->get_name().find(OPEN_INTERACTION_NODE_NAME) == -1) {
			currentNode->cast_to<DialogBox>(currentNode)->connect("just_started", this, "on_dialogBox_just_started");
			currentNode->cast_to<DialogBox>(currentNode)->connect("just_hided", this, "on_dialogBox_just_hided");

			continueConnecting = false;
		}
	}

	if (continueConnecting) {
		for (int i = 0; i < currentNode->get_child_count(); i++)
			connectNeededSignals(currentNode->get_child(i));
	}
}

bool MainScene::canPlayerMoove() const
{
	return
		!m_mouseIsInButton &&
		!m_inventory->get_parent()->cast_to<InventoryButton>(m_inventory->get_parent())->isInventoryOpen() &&
		!m_playerIsInteracting &&
		!m_inOpenInteraction &&
		Utils::isInsideRoom(get_local_mouse_position());
}

void MainScene::on_room_interaction_just_played()
{
	m_playerIsInteracting = true;
}

void MainScene::on_room_interaction_finished()
{
	m_playerIsInteracting = false;
}

void MainScene::on_openInteraction_just_played()
{
	m_inOpenInteraction = true;
	on_dialogBox_just_started();
}

void MainScene::on_openInteraction_finished()
{
	m_inOpenInteraction = false;
	on_dialogBox_just_hided();
}

void MainScene::on_mouse_entered_button()
{
	m_mouseIsInButton = true;
}

void MainScene::on_mouse_exited_button()
{
	m_mouseIsInButton = false;
}

void MainScene::on_dialogBox_just_started()
{
	m_inventory->get_parent()->cast_to<InventoryButton>(m_inventory->get_parent())->hideButton();
}

void MainScene::on_dialogBox_just_hided()
{
	m_inventory->get_parent()->cast_to<InventoryButton>(m_inventory->get_parent())->displayButton();
}

MainScene::MainScene()
{
	m_player = nullptr;
	m_camera = nullptr;
	m_inventory = nullptr;
	m_room1 = nullptr;
	m_room2 = nullptr;
	m_playerIsInteracting = false;
	m_inOpenInteraction = false;
	m_mouseIsInButton = false;
	m_inputManager = nullptr;
}

MainScene::~MainScene()
{
}

void MainScene::_init()
{
}