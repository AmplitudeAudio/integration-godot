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

#include "amplitude_gdextension.h"

using namespace SparkyStudios::Audio::Amplitude;

#define RETURN_IF_NOT_INITIALIZED(x)                                                        \
	if (!is_initialized()) {                                                                \
		ERR_PRINT("Amplitude engine is not initialized. Please call 'init' method first."); \
		return x;                                                                           \
	}

#define RETURN_IF_NOT_INITIALIZED_VOID                                                      \
	if (!is_initialized()) {                                                                \
		ERR_PRINT("Amplitude engine is not initialized. Please call 'init' method first."); \
		return;                                                                             \
	}

#define AM_ID(node) (node->get_index(true) + 1)

namespace godot {
Amplitude *Amplitude::singleton = nullptr;

void Amplitude::_bind_methods() {
	// ClassDB::bind_method(D_METHOD("load_bank", "bank_path", "bank_id"), &Amplitude::load_bank);
	// ClassDB::bind_method(D_METHOD("unload_bank", "bank_id"), &Amplitude::unload_bank);

	ClassDB::bind_method(D_METHOD("add_entity", "node"), &Amplitude::add_entity);
	ClassDB::bind_method(D_METHOD("remove_entity", "node"), &Amplitude::remove_entity);
	ClassDB::bind_method(D_METHOD("set_entity_transform_2d", "node", "transform"), &Amplitude::set_entity_transform_2d);
	ClassDB::bind_method(D_METHOD("set_entity_transform_3d", "node", "transform"), &Amplitude::set_entity_transform_3d);

	ClassDB::bind_method(D_METHOD("add_listener", "node"), &Amplitude::add_listener);
	ClassDB::bind_method(D_METHOD("remove_listener", "node"), &Amplitude::remove_listener);
	ClassDB::bind_method(D_METHOD("set_listener_transform_2d", "node", "transform"), &Amplitude::set_listener_transform_2d);
	ClassDB::bind_method(D_METHOD("set_listener_transform_3d", "node", "transform"), &Amplitude::set_listener_transform_3d);
	ClassDB::bind_method(D_METHOD("set_default_listener", "node"), &Amplitude::set_default_listener);

	// TODO: ClassDB::bind_method(D_METHOD("trigger_event", "node", "event_name"), &Amplitude::trigger_event);

	ClassDB::bind_method(D_METHOD("is_initialized"), &Amplitude::is_initialized);

	ClassDB::bind_method(D_METHOD("init"), &Amplitude::init);
	ClassDB::bind_method(D_METHOD("advance_frame", "delta_time"), &Amplitude::advance_frame);
	ClassDB::bind_method(D_METHOD("shutdown"), &Amplitude::shutdown);
}

Amplitude *Amplitude::get_singleton() {
	return singleton;
}

Amplitude::Amplitude() {
	ERR_FAIL_COND(singleton != nullptr);
	singleton = this;

	_file_system = nullptr;
}

Amplitude::~Amplitude() {
	shutdown();

	ERR_FAIL_COND(singleton != this);
	singleton = nullptr;
}

bool Amplitude::load_bank(const String &bank_path, uint64_t &bank_id) {
	RETURN_IF_NOT_INITIALIZED(false);

	amLogDebug("Loading soundbank: %s", bank_path.utf8().get_data());

#ifdef AM_WCHAR_SUPPORTED
	const bool success = amEngine->LoadSoundBank(bank_path.wide_string().get_data(), bank_id);
#else
	const bool success = amEngine->LoadSoundBank(bank_path.utf8().get_data(), bank_id);
#endif

#ifdef AM_DEBUG
	if (success) {
		amLogDebug("Loaded soundbank %s, with ID " AM_ID_CHAR_FMT, bank_path.utf8().get_data(), bank_id);
	}
#endif

	// Start loading sound files.
	amEngine->StartLoadSoundFiles();
	while (!amEngine->TryFinalizeLoadSoundFiles())
		OS::get_singleton()->delay_msec(1);

	return success;
}

void Amplitude::unload_bank(uint64_t bank_id) {
	RETURN_IF_NOT_INITIALIZED_VOID;

	amLogDebug("Unloading soundbank with ID " AM_ID_CHAR_FMT, bank_id);

	amEngine->UnloadSoundBank(bank_id);
}

void Amplitude::add_entity(const Node *node) {
	RETURN_IF_NOT_INITIALIZED_VOID;

	AM_UNUSED(amEngine->AddEntity(AM_ID(node)));
}

void Amplitude::remove_entity(const godot::Node *node) {
	RETURN_IF_NOT_INITIALIZED_VOID;

	amEngine->RemoveEntity(AM_ID(node));
}

SparkyStudios::Audio::Amplitude::Entity Amplitude::get_entity(const godot::Node *node) {
	RETURN_IF_NOT_INITIALIZED({});

	return amEngine->GetEntity(AM_ID(node));
}

void Amplitude::set_entity_transform_2d(const godot::Node *node, const Transform2D &transform) {
	RETURN_IF_NOT_INITIALIZED_VOID;

	const auto &e = amEngine->GetEntity(AM_ID(node));
	if (!e.Valid())
		return;

	const auto &position = transform.get_origin();
	e.SetLocation(AM_V3(position.x, position.y, 0.0f));

	const auto &rotation = transform.get_rotation();
	e.SetOrientation(SparkyStudios::Audio::Amplitude::Orientation(AM_QFromAxisAngle_RH(AM_V3(0.0f, 0.0f, 1.0f), rotation)));
}

void Amplitude::set_entity_transform_3d(const godot::Node *node, const Transform3D &transform) {
	RETURN_IF_NOT_INITIALIZED_VOID;

	const auto &e = amEngine->GetEntity(AM_ID(node));
	if (!e.Valid())
		return;

	const auto &position = transform.get_origin();
	e.SetLocation(AM_V3(position.x, position.y, position.z));

	Vector3 axis;
	real_t angle;
	transform.get_basis().get_rotation_axis_angle(axis, angle);
	e.SetOrientation(SparkyStudios::Audio::Amplitude::Orientation(AM_QFromAxisAngle_RH(AM_V3(axis.x, axis.y, axis.z), angle)));
}

void Amplitude::add_listener(const godot::Node *node) {
	RETURN_IF_NOT_INITIALIZED_VOID;

	AM_UNUSED(amEngine->AddListener(AM_ID(node)));
}

void Amplitude::remove_listener(const godot::Node *node) {
	RETURN_IF_NOT_INITIALIZED_VOID;

	amEngine->RemoveListener(AM_ID(node));
}

SparkyStudios::Audio::Amplitude::Listener Amplitude::get_listener(const godot::Node *node) {
	RETURN_IF_NOT_INITIALIZED({});

	return amEngine->GetListener(AM_ID(node));
}

void Amplitude::set_listener_transform_2d(const godot::Node *node, const Transform2D &transform) {
	RETURN_IF_NOT_INITIALIZED_VOID;

	const auto &l = amEngine->GetListener(AM_ID(node));
	if (!l.Valid())
		return;

	const auto &position = transform.get_origin();
	l.SetLocation(AM_V3(position.x, position.y, 0.0f));

	const auto &rotation = transform.get_rotation();
	l.SetOrientation(SparkyStudios::Audio::Amplitude::Orientation(AM_QFromAxisAngle_RH(AM_V3(0.0f, 0.0f, 1.0f), rotation)));
}

void Amplitude::set_listener_transform_3d(const godot::Node *node, const Transform3D &transform) {
	RETURN_IF_NOT_INITIALIZED_VOID;

	const auto &l = amEngine->GetListener(AM_ID(node));
	if (!l.Valid())
		return;

	const auto &position = transform.get_origin();
	l.SetLocation(AM_V3(position.x, position.y, position.z));

	Vector3 axis;
	real_t angle;
	transform.get_basis().get_rotation_axis_angle(axis, angle);
	l.SetOrientation(SparkyStudios::Audio::Amplitude::Orientation(AM_QFromAxisAngle_RH(AM_V3(axis.x, axis.y, axis.z), angle)));
}

void Amplitude::set_default_listener(const godot::Node *node) {
	RETURN_IF_NOT_INITIALIZED_VOID;

	if (node == nullptr) {
		amEngine->SetDefaultListener(nullptr);
	} else {
		amEngine->SetDefaultListener(AM_ID(node));
	}
}

EventCanceler Amplitude::trigger_event(const godot::Node *node, const String &event_name) {
	RETURN_IF_NOT_INITIALIZED({});

	return amEngine->Trigger(event_name.utf8().get_data(), get_entity(node));
}

bool Amplitude::is_initialized() {
	return amEngine->IsInitialized();
}

void Amplitude::init() {
	ProjectSettings *settings = ProjectSettings::get_singleton();

	if (settings == nullptr) {
		UtilityFunctions::printerr("[Amplitude] Cannot read project settings. Amplitude Audio cannot be initialized.");
		return;
	}

	Logger::SetLogger(&_logger);

	UtilityFunctions::printerr("Amplitude Audio is initializing...");

	// Memory Manager
	MemoryManager::Initialize(); // TODO: Implement a MemoryAllocator based on godot's memory management system.

	// File System
	if (settings->has_setting(AmplitudeSettings::PROJECT_SETTINGS_PATH)) {
		_project_path = settings->get_setting(AmplitudeSettings::PROJECT_SETTINGS_PATH);
		_file_system = ampoolnew(eMemoryPoolKind_Engine, AmplitudeFileSystem);
	}

	if (_file_system == nullptr) {
		UtilityFunctions::printerr("Could not initialize file system. Amplitude Audio cannot be initialized.");
		shutdown();
		return;
	}

#ifdef AM_WCHAR_SUPPORTED
	_file_system->SetBasePath(_project_path.wide_string().get_data());
#else
	_file_system->SetBasePath(_project_path.utf8().get_data());
#endif

	amEngine->SetFileSystem(_file_system);

	amEngine->StartOpenFileSystem();
	while (!amEngine->TryFinalizeOpenFileSystem())
		OS::get_singleton()->delay_msec(1);

	// Plugins
	SparkyStudios::Audio::Amplitude::Engine::RegisterDefaultPlugins();

	// Engine Initialization
	String engine_config;
	if (settings->has_setting(AmplitudeSettings::PROJECT_SETTINGS_ENGINE_CONFIG)) {
		engine_config = settings->get_setting(AmplitudeSettings::PROJECT_SETTINGS_ENGINE_CONFIG);
	}

	if (engine_config.is_empty()) {
		amLogError("No engine configuration found. Amplitude Audio cannot be initialized.");
		shutdown();
		return;
	}

#ifdef AM_WCHAR_SUPPORTED
	if (!amEngine->Initialize(engine_config.wide_string().get_data()))
#else
	if (!amEngine->Initialize(engine_config.utf8().get_data()))
#endif
	{
		amLogError("Could not initialize engine. Amplitude Audio cannot be initialized.");
		shutdown();
		return;
	}

	// TODO: Init Sound Bank
}

void Amplitude::advance_frame(double delta_time) {
	amEngine->AdvanceFrame(delta_time);
}

void Amplitude::shutdown() {
	if (amEngine->IsInitialized()) {
		amEngine->UnloadSoundBanks();
		amEngine->Deinitialize();
	}

	if (_file_system != nullptr) {
		// Close the file system
		amEngine->StartCloseFileSystem();
		while (!amEngine->TryFinalizeCloseFileSystem())
			OS::get_singleton()->delay_msec(1);

		ampooldelete(eMemoryPoolKind_Engine, AmplitudeFileSystem, (AmplitudeFileSystem *)_file_system);
		_file_system = nullptr;
	}

	// Unregister all default plugins
	SparkyStudios::Audio::Amplitude::Engine::UnregisterDefaultPlugins();

	// Destroy the Amplitude engine instance
	SparkyStudios::Audio::Amplitude::Engine::DestroyInstance();

	amLogInfo("Amplitude Engine deinitialized successfully.");
}
} //namespace godot