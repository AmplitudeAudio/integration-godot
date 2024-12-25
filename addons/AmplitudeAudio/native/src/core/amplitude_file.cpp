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

#include "amplitude_file.h"

using namespace SparkyStudios::Audio::Amplitude;

namespace godot {
AmplitudeFile::AmplitudeFile(const String &path, SparkyStudios::Audio::Amplitude::eFileOpenMode mode) {
	_file = FileAccess::open(path, mode == eFileOpenMode_Read ? FileAccess::READ : mode == eFileOpenMode_Write ? FileAccess::WRITE
																											   : FileAccess::READ_WRITE);
}

AmplitudeFile::~AmplitudeFile() {
	if (IsValid())
		_file->close();

	_file.unref();
}

AmOsString AmplitudeFile::GetPath() const {
	return IsValid() ? AM_STRING_TO_OS_STRING(_file->get_path_absolute().utf8().get_data()) : AM_OS_STRING("");
}

bool AmplitudeFile::Eof() {
	return IsValid() ? _file->eof_reached() : true;
}

AmSize AmplitudeFile::Read(AmUInt8Buffer dst, AmSize bytes) {
	return IsValid() ? _file->get_buffer(dst, bytes) : 0;
}

AmSize AmplitudeFile::Write(const AmConstUInt8Buffer src, AmSize bytes) {
	if (IsValid()) {
		const AmSize current = Length();
		_file->store_buffer(src, bytes);
		const AmSize new_length = Length();
		return new_length - current;
	}

	return 0;
}

AmSize AmplitudeFile::Length() {
	return IsValid() ? _file->get_length() : 0;
}

void AmplitudeFile::Seek(AmInt64 offset, eFileSeekOrigin origin) {
	if (!IsValid())
		return;

	const AmInt64 current_position = Position();
	const AmInt64 file_length = Length();

	switch (origin) {
		case eFileSeekOrigin_Start:
			_file->seek(offset);
			break;

		case eFileSeekOrigin_Current:
			_file->seek(current_position + offset);
			break;

		case eFileSeekOrigin_End:
			_file->seek(file_length + offset);
			break;
	}
}

AmSize AmplitudeFile::Position() {
	return IsValid() ? _file->get_position() : 0;
}

AmVoidPtr AmplitudeFile::GetPtr() {
	return IsValid() ? _file.ptr() : nullptr;
}

bool AmplitudeFile::IsValid() const {
	return _file.is_valid();
}
} //namespace godot
