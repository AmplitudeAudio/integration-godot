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

#include "amplitude_filesystem.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace SparkyStudios::Audio::Amplitude;

namespace godot {
void AmplitudeFileSystem::SetBasePath(const AmOsString &basePath) {
	_base_path = basePath;
}

const AmOsString &AmplitudeFileSystem::GetBasePath() const {
	return _base_path;
}

AmOsString AmplitudeFileSystem::ResolvePath(const AmOsString &path) const {
	if (String(path.c_str()).is_absolute_path())
		return path;

	auto res = Join({ _base_path, path });
	UtilityFunctions::print("Resolved path: ", res.c_str());
	return res;
}

bool AmplitudeFileSystem::Exists(const SparkyStudios::Audio::Amplitude::AmOsString &path) const {
	return _directory.is_valid() ? _directory->file_exists(path.c_str()) : false;
}

bool AmplitudeFileSystem::IsDirectory(const SparkyStudios::Audio::Amplitude::AmOsString &path) const {
	return _directory.is_valid() ? _directory->dir_exists(ResolvePath(path).c_str()) : false;
}

SparkyStudios::Audio::Amplitude::AmOsString AmplitudeFileSystem::Join(const std::vector<SparkyStudios::Audio::Amplitude::AmOsString> &parts) const {
	AmOsString result = parts[0];
	for (size_t i = 1; i < parts.size(); ++i)
		result += AM_OS_STRING("/") + parts[i];

	return result;
}

std::shared_ptr<SparkyStudios::Audio::Amplitude::File> AmplitudeFileSystem::OpenFile(const SparkyStudios::Audio::Amplitude::AmOsString &path, SparkyStudios::Audio::Amplitude::eFileOpenMode mode) const {
	return std::make_shared<AmplitudeFile>(ResolvePath(path).c_str(), mode);
}

void AmplitudeFileSystem::StartOpenFileSystem() {
	_directory = DirAccess::open(_base_path.c_str());
	if (_directory.is_null())
		UtilityFunctions::printerr("Failed to open filesystem at path: ", _base_path.c_str());
}

bool AmplitudeFileSystem::TryFinalizeOpenFileSystem() {
	return _directory.is_valid();
}

void AmplitudeFileSystem::StartCloseFileSystem() {
	_directory.unref();
}

bool AmplitudeFileSystem::TryFinalizeCloseFileSystem() {
	return _directory.is_null();
}
} //namespace godot