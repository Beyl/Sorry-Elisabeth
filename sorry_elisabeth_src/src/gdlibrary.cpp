/**
 * Register the classes to be abble to use them in godot
 */

#include "game/Player.h"
#include "game/MainScene.h"
#include "ui/dialog_box/DialogBox.h"

#include "../tests/game/PlayerTest.h"
#include "../tests/game/CameraTest.h"
#include "../tests/utils/UtilsTest.h"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) { Godot::gdnative_init(o); }

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) { Godot::gdnative_terminate(o); }

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	Godot::nativescript_init(handle);

	register_class<MainScene>();
	register_class<Player>();
	register_class<Camera>();
	register_class<DialogBox>();

	//Tests
	register_class<PlayerTest>();
	register_class<CameraTest>();
	register_class<UtilsTest>();
}