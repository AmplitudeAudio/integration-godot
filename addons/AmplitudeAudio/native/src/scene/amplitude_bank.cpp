#include "amplitude_bank.h"

using namespace godot;
using namespace SparkyStudios::Audio::Amplitude;

AmplitudeBank::AmplitudeBank() {
	_bank_path = "";
}

void AmplitudeBank::_enter_tree() {
	ProjectSettings *settings = ProjectSettings::get_singleton();

	if (settings == nullptr)
		return;

	if (settings->has_setting("audio/amplitude/init-bank")) {
		_bank_path = settings->get_setting("audio/amplitude/init-bank");
	}
}

void AmplitudeBank::_ready() {
	if (_load_on_ready) {
		load_bank();
	}
}

void AmplitudeBank::_exit_tree() {
	if (_bank_loaded)
		unload_bank();
}

void AmplitudeBank::load_bank() {
	Amplitude *amplitude = Amplitude::get_singleton();

	if (amplitude == nullptr)
		return;

	if (_bank_loaded)
		unload_bank();

	if (_bank_path.is_empty())
		return;

	_bank_loaded = amplitude->load_bank(_bank_path);
}

void AmplitudeBank::unload_bank() {
	Amplitude *amplitude = Amplitude::get_singleton();

	if (amplitude == nullptr)
		return;

	if (!_bank_loaded)
		return;

	amplitude->unload_bank(_bank_path);
	_bank_loaded = false;
}

void AmplitudeBank::set_bank_path(const String &path) {
	_bank_path = path;
}

String godot::AmplitudeBank::get_bank_path() const {
	return _bank_path;
}

void AmplitudeBank::set_load_on_ready(bool load_on_ready) {
	_load_on_ready = load_on_ready;
}

bool godot::AmplitudeBank::is_load_on_ready() const {
	return _load_on_ready;
}

void AmplitudeBank::_bind_methods() {
	ClassDB::bind_method(D_METHOD("load_bank"), &AmplitudeBank::load_bank);
	ClassDB::bind_method(D_METHOD("unload_bank"), &AmplitudeBank::unload_bank);
	ClassDB::bind_method(D_METHOD("set_bank_path", "path"), &AmplitudeBank::set_bank_path);
	ClassDB::bind_method(D_METHOD("get_bank_path"), &AmplitudeBank::get_bank_path);
	ClassDB::bind_method(D_METHOD("set_load_on_ready", "load_on_ready"), &AmplitudeBank::set_load_on_ready);
	ClassDB::bind_method(D_METHOD("is_load_on_ready"), &AmplitudeBank::is_load_on_ready);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "bank_path", PROPERTY_HINT_NONE), "set_bank_path", "get_bank_path");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "load_on_ready", PROPERTY_HINT_NONE), "set_load_on_ready", "is_load_on_ready");
}
