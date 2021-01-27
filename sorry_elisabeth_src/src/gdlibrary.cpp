/**
 * Register the classes to be abble to use them in godot
 */

#include "game/MainScene.h"
#include "game/OpenInteraction.h"
#include "game/InteractionTable.h"

#include "../tests/utils/UtilsTest.h"
#include "../tests/game/PlayerTest.h"
#include "../tests/game/CameraTest.h"
#include "../tests/game/DialogBoxTest.h"
#include "../tests/game/FadeBackgroundTest.h"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) { Godot::gdnative_init(o); }

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) { Godot::gdnative_terminate(o); }

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	Godot::nativescript_init(handle);

	//Main scene game classes
	register_class<MainScene>();
		register_class<Player>();
		register_class<Camera>();
			register_class<InteractionTable>();
				register_class<ExamineInteraction>();
				register_class<OpenInteraction>();
					register_class<SearchPlace>();
	
	register_class<DialogBox>();
	register_class<FadeBackground>();

	//Test classes
	register_class<UtilsTest>();
	register_class<PlayerTest>();
	register_class<CameraTest>();
	register_class<FadeBackgroundTest>();
	register_class<DialogBoxTest>();
}