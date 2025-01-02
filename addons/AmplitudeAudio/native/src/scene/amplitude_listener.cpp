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

#include "amplitude_listener.h"

using namespace godot;
using namespace SparkyStudios::Audio::Amplitude;

void AmplitudeListener2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_is_default", "is_default"), &AmplitudeListener2D::set_is_default);
	ClassDB::bind_method(D_METHOD("is_default"), &AmplitudeListener2D::is_default);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_default", PROPERTY_HINT_NONE), "set_is_default", "is_default");
}

void AmplitudeListener2D::_enter_tree() {
	if (godot::Engine::get_singleton()->is_editor_hint()) {
		_is_editor = true;
		return;
	}

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->add_listener(this);

	if (_is_default)
		am->set_default_listener(this);
}

void AmplitudeListener2D::_exit_tree() {
	if (godot::Engine::get_singleton()->is_editor_hint()) {
		_is_editor = true;
		return;
	}

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->remove_listener(this);
}

void AmplitudeListener2D::_process(double delta) {
	if (_is_editor)
		return;

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->set_listener_transform_2d(this, get_global_transform());
}

void AmplitudeListener2D::set_is_default(bool is_default) {
	_is_default = is_default;

	Amplitude *am = Amplitude::get_singleton();
	if (am != nullptr && !_is_editor) {
		am->set_default_listener(is_default ? this : nullptr);
	}
}

bool AmplitudeListener2D::is_default() const {
	return _is_default;
}

void AmplitudeListener2D::set_directivity(float directivity) {
	_directivity = directivity;

	Amplitude *am = Amplitude::get_singleton();
	if (am != nullptr && !_is_editor) {
		am->get_listener(this).SetDirectivity(_directivity, _sharpness);
	}
}

float AmplitudeListener2D::get_directivity() const {
	return _directivity;
}

void AmplitudeListener2D::set_sharpness(float sharpness) {
	_sharpness = sharpness;

	Amplitude *am = Amplitude::get_singleton();
	if (am != nullptr && !_is_editor) {
		am->get_listener(this).SetDirectivity(_directivity, _sharpness);
	}
}

float AmplitudeListener2D::get_sharpness() const {
	return _sharpness;
}

void AmplitudeListener3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_is_default", "is_default"), &AmplitudeListener3D::set_is_default);
	ClassDB::bind_method(D_METHOD("is_default"), &AmplitudeListener3D::is_default);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_default", PROPERTY_HINT_NONE), "set_is_default", "is_default");
}

void AmplitudeListener3D::_enter_tree() {
	if (godot::Engine::get_singleton()->is_editor_hint()) {
		_is_editor = true;
		return;
	}

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->add_listener(this);

	if (_is_default)
		am->set_default_listener(this);
}

void AmplitudeListener3D::_exit_tree() {
	if (godot::Engine::get_singleton()->is_editor_hint()) {
		_is_editor = true;
		return;
	}

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->remove_listener(this);
}

void AmplitudeListener3D::_process(double delta) {
	if (_is_editor)
		return;

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->set_listener_transform_3d(this, get_global_transform());
}

void AmplitudeListener3D::set_is_default(bool is_default) {
	_is_default = is_default;

	Amplitude *am = Amplitude::get_singleton();
	if (am != nullptr && !_is_editor) {
		am->set_default_listener(is_default ? this : nullptr);
	}
}

bool AmplitudeListener3D::is_default() const {
	return _is_default;
}

void AmplitudeListener3D::set_directivity(float directivity) {
	_directivity = directivity;

	Amplitude *am = Amplitude::get_singleton();
	if (am != nullptr && !_is_editor) {
		am->get_listener(this).SetDirectivity(_directivity, _sharpness);
	}
}

float AmplitudeListener3D::get_directivity() const {
	return _directivity;
}

void AmplitudeListener3D::set_sharpness(float sharpness) {
	_sharpness = sharpness;

	Amplitude *am = Amplitude::get_singleton();
	if (am != nullptr && !_is_editor) {
		am->get_listener(this).SetDirectivity(_directivity, _sharpness);
	}
}

float AmplitudeListener3D::get_sharpness() const {
	return _sharpness;
}
