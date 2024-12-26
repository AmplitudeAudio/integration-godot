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

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/thread.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "core/amplitude_filesystem.h"
#include "core/amplitude_logger.h"
#include "core/amplitude_settings.h"

#include <SparkyStudios/Audio/Amplitude/Amplitude.h>

namespace godot {
class Amplitude : public Object {
	GDCLASS(Amplitude, Object);

private:
	SparkyStudios::Audio::Amplitude::FileSystem *_file_system;
	String _project_path;

	AmplitudeLogger _logger;

protected:
	static Amplitude *singleton;
	static void _bind_methods();

public:
	static Amplitude *get_singleton();

	Amplitude();
	~Amplitude();

	bool load_bank(const String &bank_path, uint64_t &bank_id);
	void unload_bank(uint64_t bank_id);

	void add_entity(const godot::Node *node);
	void remove_entity(const godot::Node *node);
	SparkyStudios::Audio::Amplitude::Entity get_entity(const godot::Node *node);
	void set_entity_transform_2d(const godot::Node *node, const Transform2D &transform);
	void set_entity_transform_3d(const godot::Node *node, const Transform3D &transform);

	void add_listener(const godot::Node *node);
	void remove_listener(const godot::Node *node);
	SparkyStudios::Audio::Amplitude::Listener get_listener(const godot::Node *node);
	void set_listener_transform_2d(const godot::Node *node, const Transform2D &transform);
	void set_listener_transform_3d(const godot::Node *node, const Transform3D &transform);
	void set_default_listener(const godot::Node *node);

	SparkyStudios::Audio::Amplitude::EventCanceler trigger_event(const godot::Node *node, const String &event_name);

	bool is_initialized();

	void init();
	void advance_frame(double delta_time);
	void shutdown();
};
} // namespace godot

#endif // AMPLITUDE_GDEXTENSION_H