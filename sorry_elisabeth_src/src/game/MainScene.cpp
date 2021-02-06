#include "MainScene.h"

using namespace godot;

void MainScene::_register_methods()
{
	register_method("_ready", &MainScene::_ready);
	register_method("_physics_process", &MainScene::_physics_process);
}

void MainScene::_ready()
{
	// Member variables initialisation
	m_inputManager = Input::get_singleton();
	m_gameSceneActive = true;

	// Get the children
	m_player = get_node("Player")->cast_to<Player>(get_node("Player"));
	m_camera = get_node("Camera")->cast_to<Camera>(get_node("Camera"));
	m_inventory = get_node("UILayer/InventoryButton/Inventory")->cast_to<Inventory>
		(get_node("UILayer/InventoryButton/Inventory"));

	// Scene initialisation
	m_player->set_position(Vector2(real_t(PLAYER_START_X), real_t(PLAYER_START_Y)));
	sendInfoToInteractions(this);
}

void MainScene::_physics_process()
{
	if (m_gameSceneActive) {
		if (m_inputManager->is_action_just_released("mouse_left_click")) {
			if (Utils::isInsideRoom(get_local_mouse_position())) {
				// If a left click is done, moove the player to the this point
				m_player->mooveTo(int(get_local_mouse_position().x));
			}
		}
	}
	sendPlayerInfoToCam();
}

void MainScene::sendPlayerInfoToCam()
{
	m_camera->setPlayerPosition(m_player->get_position());
	m_camera->setPlayerDirection(m_player->getDirection());
}

void MainScene::sendInfoToInteractions(Node* currentNode)
{
	bool hasBeenSet = false;

	if (currentNode->get_name() == TAKE_HANDBAG_INTERACTION_NODE_NAME) {
		currentNode->cast_to<TakeHandbagInteraction>(currentNode)->setPlayer(m_player);
		currentNode->cast_to<TakeHandbagInteraction>(currentNode)->setInventory(m_inventory);
		hasBeenSet = true;
	}
	else if (currentNode->get_name() == TAKE_INTERACTION_NODE_NAME) {
		currentNode->cast_to<TakeInteraction>(currentNode)->setInventory(m_inventory);
	}

	if (!hasBeenSet) {
		for (int i = 0; i < currentNode->get_child_count(); i++)
			sendInfoToInteractions(currentNode->get_child(i));
	}
}

MainScene::MainScene()
{
	m_player = 0;
	m_camera = 0;
	m_inventory = 0;
	m_gameSceneActive = true;
	m_inputManager = 0;
}

MainScene::~MainScene()
{
}

void MainScene::_init()
{
}