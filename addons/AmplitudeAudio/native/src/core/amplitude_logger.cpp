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

#include "amplitude_logger.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace SparkyStudios::Audio::Amplitude;

namespace godot {
void AmplitudeLogger::Log(eLogMessageLevel level, const char *file, int line, const AmString &message) {
	switch (level) {
		case eLogMessageLevel_Critical:
			UtilityFunctions::printerr("[Amplitude] Critical: (", file, ":", line, ") - ", message.c_str());
			break;

		case eLogMessageLevel_Debug:
			UtilityFunctions::print("[Amplitude] Debug: (", file, ":", line, ") - ", message.c_str());
			break;

		case eLogMessageLevel_Error:
			UtilityFunctions::printerr("[Amplitude] Error: (", file, ":", line, ") - ", message.c_str());
			break;

		case eLogMessageLevel_Info:
			UtilityFunctions::print("[Amplitude] Info: (", file, ":", line, ") - ", message.c_str());
			break;

		case eLogMessageLevel_Warning:
			UtilityFunctions::print("[Amplitude] Warning: (", file, ":", line, ") - ", message.c_str());
			break;

		case eLogMessageLevel_Success:
			UtilityFunctions::print("[Amplitude] Success: (", file, ":", line, ") - ", message.c_str());
			break;
	}
}
} // namespace godot