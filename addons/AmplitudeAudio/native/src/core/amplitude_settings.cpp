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

#include "amplitude_settings.h"

namespace godot {
void AmplitudeSettings::_bind_methods() {}

AmplitudeSettings::AmplitudeSettings() {
	add_amplitude_settings();

	if (Engine::get_singleton()->is_editor_hint()) {
		Error error = ProjectSettings::get_singleton()->save();
		if (error) {
			UtilityFunctions::push_error(String("[Amplitude] Encountered error {0} while saving Project Settings.")
							.format(Array::make(error)));
		} else {
			UtilityFunctions::print("[Amplitude] Saved Project Settings.");
		}
	}
}

void AmplitudeSettings::add_amplitude_settings() {
	// Common User Settings
	add_setting(PROJECT_SETTINGS_PATH, String("res://amplitude_project"), Variant::Type::STRING, PROPERTY_HINT_DIR, "res://amplitude_project");
	add_setting(PROJECT_SETTINGS_INIT_BANK, String("init.ambank"), Variant::Type::STRING, PROPERTY_HINT_FILE, "Amplitude Audio Bank (*.ambank)");
	add_setting(PROJECT_SETTINGS_ENGINE_CONFIG, String("pc.config.amconfig"), Variant::Type::STRING, PROPERTY_HINT_FILE, "Amplitude Engine Config (*.amconfig)");

	add_setting(USER_SETTINGS_SUSPEND_ON_FOCUS_LOST, false, Variant::Type::BOOL);
}

void AmplitudeSettings::add_setting(const String &name, const Variant &default_value, Variant::Type type, PropertyHint hint,
		const String &hint_string, int usage) {
	Dictionary setting;
	setting["name"] = name;
	setting["type"] = type;
	setting["hint"] = hint;
	setting["hint_string"] = hint_string;
	setting["usage"] = usage;

	if (ProjectSettings::get_singleton()->has_setting(name)) {
		ProjectSettings::get_singleton()->add_property_info(setting);
		return;
	}

	ProjectSettings::get_singleton()->set_setting(name, default_value);
	ProjectSettings::get_singleton()->add_property_info(setting);
}
} //namespace godot