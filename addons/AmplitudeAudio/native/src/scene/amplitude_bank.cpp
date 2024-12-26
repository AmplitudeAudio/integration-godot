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

#include "amplitude_bank.h"

#include "core/amplitude_settings.h"

using namespace godot;
using namespace SparkyStudios::Audio::Amplitude;

AmplitudeBank::AmplitudeBank() {
	_bank_path = "";
}

void AmplitudeBank::_enter_tree() {
	ProjectSettings *settings = ProjectSettings::get_singleton();

	if (settings == nullptr)
		return;

	if (settings->has_setting(AmplitudeSettings::PROJECT_SETTINGS_INIT_BANK)) {
		_bank_path = settings->get_setting(AmplitudeSettings::PROJECT_SETTINGS_INIT_BANK);
	}
}

void AmplitudeBank::_ready() {
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (_load_on_ready) {
		load_bank();
	}
}

void AmplitudeBank::_exit_tree() {
	if (_bank_loaded)
		unload_bank();
}

void AmplitudeBank::load_bank() {
	Amplitude *amplitude = Amplitude::get_singleton();

	if (amplitude == nullptr)
		return;

	if (_bank_loaded)
		unload_bank();

	if (_bank_path.is_empty())
		return;

	_bank_loaded = amplitude->load_bank(_bank_path, _bank_id);
}

void AmplitudeBank::unload_bank() {
	Amplitude *amplitude = Amplitude::get_singleton();

	if (amplitude == nullptr)
		return;

	if (!_bank_loaded)
		return;

	amplitude->unload_bank(_bank_id);
	_bank_loaded = false;
}

void AmplitudeBank::set_bank_path(const String &path) {
	_bank_path = path;
}

String AmplitudeBank::get_bank_path() const {
	return _bank_path;
}

void AmplitudeBank::set_load_on_ready(bool load_on_ready) {
	_load_on_ready = load_on_ready;
}

bool AmplitudeBank::is_load_on_ready() const {
	return _load_on_ready;
}

void AmplitudeBank::_bind_methods() {
	ClassDB::bind_method(D_METHOD("load_bank"), &AmplitudeBank::load_bank);
	ClassDB::bind_method(D_METHOD("unload_bank"), &AmplitudeBank::unload_bank);
	ClassDB::bind_method(D_METHOD("set_bank_path", "path"), &AmplitudeBank::set_bank_path);
	ClassDB::bind_method(D_METHOD("get_bank_path"), &AmplitudeBank::get_bank_path);
	ClassDB::bind_method(D_METHOD("set_load_on_ready", "load_on_ready"), &AmplitudeBank::set_load_on_ready);
	ClassDB::bind_method(D_METHOD("is_load_on_ready"), &AmplitudeBank::is_load_on_ready);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "bank_path", PROPERTY_HINT_FILE, "Amplitude Sound Bank (*.ambank)"), "set_bank_path", "get_bank_path");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "load_on_ready", PROPERTY_HINT_NONE), "set_load_on_ready", "is_load_on_ready");
}
