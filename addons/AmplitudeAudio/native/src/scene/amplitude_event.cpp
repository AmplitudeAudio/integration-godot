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

#include "amplitude_event.h"

using namespace godot;
using namespace SparkyStudios::Audio::Amplitude;

void AmplitudeEvent2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("trigger"), &AmplitudeEvent2D::trigger);
	ClassDB::bind_method(D_METHOD("cancel"), &AmplitudeEvent2D::cancel);

	ClassDB::bind_method(D_METHOD("set_event", "event"), &AmplitudeEvent2D::set_event);
	ClassDB::bind_method(D_METHOD("get_event"), &AmplitudeEvent2D::get_event);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "event", PROPERTY_HINT_NONE), "set_event", "get_event");

	ClassDB::bind_method(D_METHOD("set_trigger_on_ready", "trigger_on_ready"), &AmplitudeEvent2D::set_trigger_on_ready);
	ClassDB::bind_method(D_METHOD("is_trigger_on_ready"), &AmplitudeEvent2D::is_trigger_on_ready);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "trigger_on_ready", PROPERTY_HINT_NONE), "set_trigger_on_ready", "is_trigger_on_ready");

	ADD_SIGNAL(MethodInfo("event_triggered", PropertyInfo(Variant::STRING, "event", PROPERTY_HINT_NONE)));
}

void AmplitudeEvent2D::_notification(int p_what) {
}

AmplitudeEvent2D::AmplitudeEvent2D() {
}

void AmplitudeEvent2D::_ready() {
	if (!_trigger_on_ready)
		return;

	trigger();
}

void AmplitudeEvent2D::_exit_tree() {
	cancel();

	AmplitudeEntity2D::_exit_tree();
}

void AmplitudeEvent2D::trigger() {
	if (_event_name.is_empty() || _is_editor)
		return;

	_canceler = Amplitude::get_singleton()->trigger_event(this, _event_name);
	emit_signal("event_triggered", _event_name);
}

void AmplitudeEvent2D::cancel() {
	if (_canceler.Valid())
		_canceler.Cancel();
}

void AmplitudeEvent2D::set_event(const String &name) {
	_event_name = name;
}

String AmplitudeEvent2D::get_event() const {
	return _event_name;
}

void AmplitudeEvent2D::set_trigger_on_ready(bool trigger_on_ready) {
	_trigger_on_ready = trigger_on_ready;

	if (is_inside_tree() && trigger_on_ready)
		trigger();
}

bool AmplitudeEvent2D::is_trigger_on_ready() const {
	return _trigger_on_ready;
}

void AmplitudeEvent3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("trigger"), &AmplitudeEvent3D::trigger);
	ClassDB::bind_method(D_METHOD("cancel"), &AmplitudeEvent3D::cancel);

	ClassDB::bind_method(D_METHOD("set_event", "event"), &AmplitudeEvent3D::set_event);
	ClassDB::bind_method(D_METHOD("get_event"), &AmplitudeEvent3D::get_event);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "event", PROPERTY_HINT_NONE), "set_event", "get_event");

	ClassDB::bind_method(D_METHOD("set_trigger_on_ready", "trigger_on_ready"), &AmplitudeEvent3D::set_trigger_on_ready);
	ClassDB::bind_method(D_METHOD("is_trigger_on_ready"), &AmplitudeEvent3D::is_trigger_on_ready);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "trigger_on_ready", PROPERTY_HINT_NONE), "set_trigger_on_ready", "is_trigger_on_ready");

	ADD_SIGNAL(MethodInfo("event_triggered", PropertyInfo(Variant::STRING, "event", PROPERTY_HINT_NONE)));
}

void AmplitudeEvent3D::_notification(int p_what) {
}

AmplitudeEvent3D::AmplitudeEvent3D() {
}

void AmplitudeEvent3D::_ready() {
	if (!_trigger_on_ready)
		return;

	trigger();
}

void AmplitudeEvent3D::_exit_tree() {
	cancel();

	AmplitudeEntity3D::_exit_tree();
}

void AmplitudeEvent3D::trigger() {
	if (_event_name.is_empty() || _is_editor)
		return;

	_canceler = Amplitude::get_singleton()->trigger_event(this, _event_name);
	emit_signal("event_triggered", _event_name);
}

void AmplitudeEvent3D::cancel() {
	if (_canceler.Valid())
		_canceler.Cancel();
}

void AmplitudeEvent3D::set_event(const String &name) {
	_event_name = name;
}

String AmplitudeEvent3D::get_event() const {
	return _event_name;
}

void AmplitudeEvent3D::set_trigger_on_ready(bool trigger_on_ready) {
	_trigger_on_ready = trigger_on_ready;

	if (is_inside_tree() && trigger_on_ready)
		trigger();
}

bool AmplitudeEvent3D::is_trigger_on_ready() const {
	return _trigger_on_ready;
}
