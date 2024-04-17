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

#include "amplitude_gdextension.h"

namespace godot {
Amplitude *Amplitude::singleton = nullptr;

void Amplitude::_bind_methods() {
	ClassDB::bind_method(D_METHOD("init"), &Amplitude::init);
	ClassDB::bind_method(D_METHOD("shutdown"), &Amplitude::shutdown);
}

Amplitude *Amplitude::get_singleton() {
	return singleton;
}

Amplitude::Amplitude() {
	ERR_FAIL_COND(singleton != nullptr);
	singleton = this;
}

Amplitude::~Amplitude() {
	ERR_FAIL_COND(singleton != this);
	singleton = nullptr;
}

void Amplitude::init() {
	UtilityFunctions::print("[Amplitude] Amplitude Audio is initializing...");
}

void Amplitude::shutdown() {
	UtilityFunctions::print("[Amplitude] Amplitude Audio is shutting down...");
}
} //namespace godot