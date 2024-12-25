// Copyright (c) 2024-present Sparky Studios. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "register_types.h"

#include "amplitude_gdextension.h"

#include "scene/amplitude_bank.h"

#include <gdextension_interface.h>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

static Amplitude *s_am = nullptr;
static AmplitudeSettings *s_settings = nullptr;

void initialize_amplitude_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<Amplitude>();
		s_am = memnew(Amplitude);
		godot::Engine::get_singleton()->register_singleton("Amplitude", s_am);

		ClassDB::register_class<AmplitudeSettings>();
		s_settings = memnew(AmplitudeSettings);

		// TODO: Register nodes here
		ClassDB::register_class<AmplitudeBank>();
	}
}

void uninitialize_amplitude_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		memdelete(s_settings);

		if (godot::Engine::get_singleton()->has_singleton("Amplitude")) {
			godot::Engine::get_singleton()->unregister_singleton("Amplitude");
			memdelete(s_am);
		}
	}
}

extern "C" GDExtensionBool GDE_EXPORT amplitude_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_object(p_get_proc_address, p_library, r_initialization);

	init_object.register_initializer(initialize_amplitude_module);
	init_object.register_terminator(uninitialize_amplitude_module);
	init_object.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SERVERS);

	return init_object.init();
}