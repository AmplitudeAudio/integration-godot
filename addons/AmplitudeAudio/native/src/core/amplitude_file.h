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

#include <godot_cpp/classes/file_access.hpp>

#include <SparkyStudios/Audio/Amplitude/IO/File.h>

namespace godot {
class AmplitudeFile : public SparkyStudios::Audio::Amplitude::File {
private:
	Ref<FileAccess> _file;

public:
	AmplitudeFile(const String &path, SparkyStudios::Audio::Amplitude::eFileOpenMode mode);
	~AmplitudeFile() override;
	SparkyStudios::Audio::Amplitude::AmOsString GetPath() const override;
	bool Eof() override;
	SparkyStudios::Audio::Amplitude::AmSize Read(SparkyStudios::Audio::Amplitude::AmUInt8Buffer dst, SparkyStudios::Audio::Amplitude::AmSize bytes) override;
	SparkyStudios::Audio::Amplitude::AmSize Write(const SparkyStudios::Audio::Amplitude::AmConstUInt8Buffer src, SparkyStudios::Audio::Amplitude::AmSize bytes) override;
	SparkyStudios::Audio::Amplitude::AmSize Length() override;
	void Seek(SparkyStudios::Audio::Amplitude::AmInt64 offset, SparkyStudios::Audio::Amplitude::eFileSeekOrigin origin) override;
	SparkyStudios::Audio::Amplitude::AmSize Position() override;
	SparkyStudios::Audio::Amplitude::AmVoidPtr GetPtr() override;
	bool IsValid() const override;
};
} //namespace godot