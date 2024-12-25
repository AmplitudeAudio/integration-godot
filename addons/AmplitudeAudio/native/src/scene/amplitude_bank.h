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

#ifndef AMPLITUDE_BANK_H
#define AMPLITUDE_BANK_H

#include "amplitude_gdextension.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/project_settings.hpp>

namespace godot {
class AmplitudeBank : public Node {
	GDCLASS(AmplitudeBank, Node);

public:
	AmplitudeBank();

	void _enter_tree() override;
	void _ready() override;
	void _exit_tree() override;

	void load_bank();
	void unload_bank();

	void set_bank_path(const String &path);
	String get_bank_path() const;

	void set_load_on_ready(bool load_on_ready);
	bool is_load_on_ready() const;

protected:
	static void _bind_methods();

private:
	String _bank_path;
	bool _load_on_ready = false;
	bool _bank_loaded = false;
	SparkyStudios::Audio::Amplitude::AmBankID _bank_id = SparkyStudios::Audio::Amplitude::kAmInvalidObjectId;
};
} //namespace godot

#endif // AMPLITUDE_BANK_H