#include "value.h"
#include "cog/constants.h"

using namespace gorc::cog::vm;

value::value()
	: type_flag(type::nothing) {
	return;
}

value::value(const value& v) {
	*this = v;
}

const value& value::operator=(const value& v) {
	type_flag = v.type_flag;
	data = v.data;

	return v;
}

value::value(int v) {
	*this = v;
}

int value::operator=(int v) {
	type_flag = type::integer;
	data.integer = v;

	return v;
}

value::operator int() const {
	switch(type_flag) {
	case type::nothing:
		return constants::default_int;

	case type::integer:
		return data.integer;

	case type::floating:
		return static_cast<int>(data.Floating);

	case type::boolean:
		return (data.Boolean) ? 1 : 0;

	case type::string:
		return constants::default_int;

	case type::vector:
		return constants::default_int;

	default:
		return constants::default_int;
	}
}

value::value(float v) {
	*this = v;
}

float value::operator=(float v) {
	type_flag = type::floating;
	data.Floating = v;

	return v;
}

value::operator float() const {
	switch(type_flag) {
	case type::nothing:
		return constants::default_float;

	case type::integer:
		return static_cast<float>(data.integer);

	case type::floating:
		return data.Floating;

	case type::boolean:
		return (data.Boolean) ? 1.0f : 0.0f;

	case type::string:
		return constants::default_float;

	case type::vector:
		return constants::default_float;

	default:
		return constants::default_float;
	}
}

value::value(bool v) {
	*this = v;
}

bool value::operator=(bool v) {
	type_flag = type::boolean;
	data.Boolean = v;

	return v;
}

value::operator bool() const {
	switch(type_flag) {
	case type::nothing:
		return false;

	case type::integer:
		return data.integer != 0;

	case type::floating:
		return data.Floating != 0.0f;

	case type::boolean:
		return data.Boolean;

	case type::string:
		return true;

	case type::vector:
		return true;

	default:
		return false;
	}
}

value::value(const char* v) {
	*this = v;
}

const char* value::operator=(const char* v) {
	type_flag = type::string;
	data.string = v;

	return v;
}

value::operator const char*() const {
	switch(type_flag) {
	case type::nothing:
		return constants::default_string;

	case type::integer:
		return constants::default_string;

	case type::floating:
		return constants::default_string;

	case type::boolean:
		return constants::default_string;

	case type::string:
		return data.string;

	case type::vector:
		return constants::default_string;

	default:
		return constants::default_string;
	}
}

value::value(const vector<3>& v) {
	*this = v;
}

const gorc::vector<3>& value::operator=(const vector<3>& v) {
	type_flag = type::vector;
	data.vector.X = math::get<math::X>(v);
	data.vector.Y = math::get<math::Y>(v);
	data.vector.Z = math::get<math::Z>(v);

	return v;
}

value::operator gorc::vector<3>() const {
	switch(type_flag) {
	case type::nothing:
		return vector<3>();

	case type::integer:
		return vector<3>();

	case type::floating:
		return vector<3>();

	case type::boolean:
		return vector<3>();

	case type::string:
		return vector<3>();

	case type::vector:
		return make_vector(data.vector.X, data.vector.Y, data.vector.Z);

	default:
		return vector<3>();
	}
}
