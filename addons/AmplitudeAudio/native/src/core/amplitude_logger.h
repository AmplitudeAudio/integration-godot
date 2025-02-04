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

#include <SparkyStudios/Audio/Amplitude/Core/Log.h>

namespace godot {
class AmplitudeLogger : public SparkyStudios::Audio::Amplitude::Logger {
protected:
	void Log(SparkyStudios::Audio::Amplitude::eLogMessageLevel level, const char *file, int line, const SparkyStudios::Audio::Amplitude::AmString &message) override;
};
} //namespace godot