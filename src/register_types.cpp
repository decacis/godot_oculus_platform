#include "register_types.h"

using namespace godot;

static GDOculusPlatform *gd_oculus_platform;

void initialize_gdoculusplatform_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<GDOPUserArray>();
	ClassDB::register_class<GDOPLeaderboardEntries>();
	ClassDB::register_class<GDOculusPlatformPromise>();
	ClassDB::register_class<GDOculusPlatform>();
	gd_oculus_platform = memnew(GDOculusPlatform);
	Engine::get_singleton()->register_singleton("GDOculusPlatform", GDOculusPlatform::get_singleton());
}

void uninitialize_gdoculusplatform_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	Engine::get_singleton()->unregister_singleton("GDOculusPlatform");
	memdelete(gd_oculus_platform);
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT
gdoculusplatform_library_init(const GDExtensionInterface *p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

	init_obj.register_initializer(initialize_gdoculusplatform_module);
	init_obj.register_terminator(uninitialize_gdoculusplatform_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
