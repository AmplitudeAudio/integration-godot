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

#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {
class AmplitudeSettings : public RefCounted {
	GDCLASS(AmplitudeSettings, RefCounted);

protected:
	static void _bind_methods();

private:
	void add_amplitude_settings();

	void add_setting(const String &name, const Variant &default_value, Variant::Type type,
			PropertyHint hint = PROPERTY_HINT_NONE, const String &hint_string = "", int usage = PROPERTY_USAGE_DEFAULT);

public:
	static constexpr char PROJECT_SETTINGS_PATH[] = "amplitude_audio/project_settings/path";
	static constexpr char PROJECT_SETTINGS_INIT_BANK[] = "amplitude_audio/project_settings/init_bank";
	static constexpr char PROJECT_SETTINGS_ENGINE_CONFIG[] = "amplitude_audio/project_settings/engine_config";

	static constexpr char USER_SETTINGS_SUSPEND_ON_FOCUS_LOST[] = "amplitude_audio/user_settings/suspend_on_focus_lost";

	AmplitudeSettings();
};
}