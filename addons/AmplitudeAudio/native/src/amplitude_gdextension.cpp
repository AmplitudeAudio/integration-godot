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

namespace godot {
Amplitude *Amplitude::singleton = nullptr;

void Amplitude::_bind_methods() {
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

bool Amplitude::load_bank(const String &bank_path) {
	UtilityFunctions::print("[Amplitude] Soundbank to load: " + bank_path);
	return true;
}

void Amplitude::unload_bank(const String &bank_path) {
	UtilityFunctions::print("[Amplitude] Soundbank to unload: " + bank_path);
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
	UtilityFunctions::printerr("File system set");

	amEngine->StartOpenFileSystem();
	while (!amEngine->TryFinalizeOpenFileSystem())
		OS::get_singleton()->delay_msec(1);

	UtilityFunctions::printerr("FIle system opened");
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