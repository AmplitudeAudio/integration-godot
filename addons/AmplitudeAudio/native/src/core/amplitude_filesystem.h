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

#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/file_access.hpp>

#include "amplitude_file.h"

#include <SparkyStudios/Audio/Amplitude/IO/FileSystem.h>

namespace godot {
class AmplitudeFileSystem : public SparkyStudios::Audio::Amplitude::FileSystem {
private:
	SparkyStudios::Audio::Amplitude::AmOsString _base_path;
	Ref<DirAccess> _directory;

public:
	void SetBasePath(const SparkyStudios::Audio::Amplitude::AmOsString &basePath) override;
	const SparkyStudios::Audio::Amplitude::AmOsString &GetBasePath() const override;
	SparkyStudios::Audio::Amplitude::AmOsString ResolvePath(const SparkyStudios::Audio::Amplitude::AmOsString &path) const override;
	bool Exists(const SparkyStudios::Audio::Amplitude::AmOsString &path) const override;
	bool IsDirectory(const SparkyStudios::Audio::Amplitude::AmOsString &path) const override;
	SparkyStudios::Audio::Amplitude::AmOsString Join(const std::vector<SparkyStudios::Audio::Amplitude::AmOsString> &parts) const override;
	std::shared_ptr<SparkyStudios::Audio::Amplitude::File> OpenFile(const SparkyStudios::Audio::Amplitude::AmOsString &path, SparkyStudios::Audio::Amplitude::eFileOpenMode mode) const override;
	void StartOpenFileSystem() override;
	bool TryFinalizeOpenFileSystem() override;
	void StartCloseFileSystem() override;
	bool TryFinalizeCloseFileSystem() override;
};
} //namespace godot