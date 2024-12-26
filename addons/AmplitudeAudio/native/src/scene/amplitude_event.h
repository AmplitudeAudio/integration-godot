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

#ifndef AMPLITUDE_EVENT_H
#define AMPLITUDE_EVENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/node3d.hpp>

#include "amplitude_gdextension.h"
#include "scene/amplitude_entity.h"

#include <SparkyStudios/Audio/Amplitude/Amplitude.h>

namespace godot {
class AmplitudeEvent2D : public AmplitudeEntity2D {
	GDCLASS(AmplitudeEvent2D, AmplitudeEntity2D);

private:
	SparkyStudios::Audio::Amplitude::EventCanceler _canceler;

	String _event_name;
	bool _trigger_on_ready = false;

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	AmplitudeEvent2D();
	virtual void _ready() override;
	virtual void _exit_tree() override;

	void trigger();
	void cancel();

	void set_event(const String &name);
	String get_event() const;

	void set_trigger_on_ready(bool trigger_on_ready);
	bool is_trigger_on_ready() const;
};

class AmplitudeEvent3D : public AmplitudeEntity3D {
	GDCLASS(AmplitudeEvent3D, AmplitudeEntity3D);

private:
	SparkyStudios::Audio::Amplitude::EventCanceler _canceler;

	String _event_name;
	bool _trigger_on_ready = false;

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	AmplitudeEvent3D();
	virtual void _ready() override;
	virtual void _exit_tree() override;

	void trigger();
	void cancel();

	void set_event(const String &name);
	String get_event() const;

	void set_trigger_on_ready(bool trigger_on_ready);
	bool is_trigger_on_ready() const;
};
} //namespace godot

#endif