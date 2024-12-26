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

#include "amplitude_entity.h"

using namespace godot;

void AmplitudeEntity2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_has_position", "has_position"), &AmplitudeEntity2D::set_has_position);
	ClassDB::bind_method(D_METHOD("has_position"), &AmplitudeEntity2D::has_position);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_position", PROPERTY_HINT_NONE), "set_has_position", "has_position");
}

void AmplitudeEntity2D::_enter_tree() {
	if (godot::Engine::get_singleton()->is_editor_hint()) {
		_is_editor = true;
		return;
	}

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->add_entity(this);
}

void AmplitudeEntity2D::_exit_tree() {
	if (godot::Engine::get_singleton()->is_editor_hint()) {
		_is_editor = true;
		return;
	}

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->remove_entity(this);
}

void AmplitudeEntity2D::_process(double delta) {
	if (!_has_position || _is_editor)
		return;

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->set_entity_transform_2d(this, get_global_transform());
}

void AmplitudeEntity2D::set_has_position(bool has_position) {
	_has_position = has_position;
}

bool AmplitudeEntity2D::has_position() const {
	return _has_position;
}

void AmplitudeEntity3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_has_position", "has_position"), &AmplitudeEntity3D::set_has_position);
	ClassDB::bind_method(D_METHOD("has_position"), &AmplitudeEntity3D::has_position);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_position", PROPERTY_HINT_NONE), "set_has_position", "has_position");
}

void AmplitudeEntity3D::_enter_tree() {
	if (godot::Engine::get_singleton()->is_editor_hint()) {
		_is_editor = true;
		return;
	}

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->add_entity(this);
}

void AmplitudeEntity3D::_exit_tree() {
	if (godot::Engine::get_singleton()->is_editor_hint()) {
		_is_editor = true;
		return;
	}

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->remove_entity(this);
}

void AmplitudeEntity3D::_process(double delta) {
	if (!_has_position || _is_editor)
		return;

	Amplitude *am = Amplitude::get_singleton();
	if (am == nullptr)
		return;

	am->set_entity_transform_3d(this, get_global_transform());
}

void AmplitudeEntity3D::set_has_position(bool has_position) {
	_has_position = has_position;
}

bool AmplitudeEntity3D::has_position() const {
	return _has_position;
}
