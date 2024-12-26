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

#ifndef AMPLITUDE_LISTENER_H
#define AMPLITUDE_LISTENER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/node3d.hpp>

#include "amplitude_gdextension.h"

#include <SparkyStudios/Audio/Amplitude/Amplitude.h>

namespace godot {
class AmplitudeListener2D : public Node2D {
	GDCLASS(AmplitudeListener2D, Node2D);

private:
	bool _is_default = false;

protected:
	static void _bind_methods();

	bool _is_editor = false;

public:
	virtual void _enter_tree() override;
	virtual void _exit_tree() override;
	virtual void _process(double delta) override;

	void set_is_default(bool is_default);
	bool is_default() const;
};

class AmplitudeListener3D : public Node3D {
	GDCLASS(AmplitudeListener3D, Node3D);

private:
	bool _is_default = false;

protected:
	static void _bind_methods();

	bool _is_editor = false;

public:
	virtual void _enter_tree() override;
	virtual void _exit_tree() override;
	virtual void _process(double delta) override;

	void set_is_default(bool is_default);
	bool is_default() const;
};
} //namespace godot

#endif