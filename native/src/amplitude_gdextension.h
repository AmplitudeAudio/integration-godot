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

#ifndef AMPLITUDE_GDEXTENSION_H
#define AMPLITUDE_GDEXTENSION_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <SparkyStudios/Audio/Amplitude/Amplitude.h>

namespace godot {
class Amplitude : public Object {
	GDCLASS(Amplitude, Object);

protected:
	static Amplitude *singleton;
	static void _bind_methods();

public:
	static Amplitude *get_singleton();

	Amplitude();
	~Amplitude();

	void init();
	void shutdown();
};
} // namespace godot

#endif // AMPLITUDE_GDEXTENSION_H