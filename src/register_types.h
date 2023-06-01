#ifndef GDOCULUSPLATFORM_REGISTER_TYPES_H
#define GDOCULUSPLATFORM_REGISTER_TYPES_H

#include <gdextension_interface.h>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "gdop_promise.h"
#include "godot_oculus_platform.h"

using namespace godot;

void initialize_gdoculusplatform_module(ModuleInitializationLevel p_level);
void uninitialize_gdoculusplatform_module(ModuleInitializationLevel p_level);

#endif // GDOCULUSPLATFORM_REGISTER_TYPES_H
