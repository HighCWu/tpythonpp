/*************************************************************************/
/*  vector3.h                                                            */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2019 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2019 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef VECTOR3_H
#define VECTOR3_H

#include "math_funcs.h"
#include "ustring.h"

class Basis;

struct Vector3 {

	enum Axis {
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
	};

	union {
		struct {
			real_t x;
			real_t y;
			real_t z;
		};

		real_t coord[3];
	};

	_FORCE_INLINE_ const real_t &operator[](int p_axis) const {

		return coord[p_axis];
	}

	_FORCE_INLINE_ real_t &operator[](int p_axis) {

		return coord[p_axis];
	}

	void set_axis(int p_axis, real_t p_value);
	real_t get_axis(int p_axis) const;

	int min_axis() const;
	int max_axis() const;

	_FORCE_INLINE_ real_t length() const;
	_FORCE_INLINE_ real_t length_squared() const;

	_FORCE_INLINE_ void normalize();
	_FORCE_INLINE_ Vector3 normalized() const;
	_FORCE_INLINE_ bool is_normalized() const;
	_FORCE_INLINE_ Vector3 inverse() const;

	_FORCE_INLINE_ void zero();

	void snap(Vector3 p_val);
	Vector3 snapped(Vector3 p_val) const;

	void rotate(const Vector3 &p_axis, real_t p_phi);
	Vector3 rotated(const Vector3 &p_axis, real_t p_phi) const;

	/* Static Methods between 2 vector3s */

	_FORCE_INLINE_ Vector3 linear_interpolate(const Vector3 &p_b, real_t p_t) const;
	_FORCE_INLINE_ Vector3 slerp(const Vector3 &p_b, real_t p_t) const;
	Vector3 cubic_interpolate(const Vector3 &p_b, const Vector3 &p_pre_a, const Vector3 &p_post_b, real_t p_t) const;
	Vector3 cubic_interpolaten(const Vector3 &p_b, const Vector3 &p_pre_a, const Vector3 &p_post_b, real_t p_t) const;
	Vector3 move_toward(const Vector3 &p_to, const real_t p_delta) const;

	_FORCE_INLINE_ Vector3 cross(const Vector3 &p_b) const;
	_FORCE_INLINE_ real_t dot(const Vector3 &p_b) const;
	_FORCE_INLINE_ Basis outer(const Vector3 &p_b) const;
	_FORCE_INLINE_ Basis to_diagonal_matrix() const;

	_FORCE_INLINE_ Vector3 abs() const;
	_FORCE_INLINE_ Vector3 floor() const;
	_FORCE_INLINE_ Vector3 sign() const;
	_FORCE_INLINE_ Vector3 ceil() const;
	_FORCE_INLINE_ Vector3 round() const;

	_FORCE_INLINE_ real_t distance_to(const Vector3 &p_b) const;
	_FORCE_INLINE_ real_t distance_squared_to(const Vector3 &p_b) const;

	_FORCE_INLINE_ Vector3 posmod(const real_t p_mod) const;
	_FORCE_INLINE_ Vector3 posmodv(const Vector3 &p_modv) const;
	_FORCE_INLINE_ Vector3 project(const Vector3 &p_b) const;

	_FORCE_INLINE_ real_t angle_to(const Vector3 &p_b) const;
	_FORCE_INLINE_ Vector3 direction_to(const Vector3 &p_b) const;

	_FORCE_INLINE_ Vector3 slide(const Vector3 &p_normal) const;
	_FORCE_INLINE_ Vector3 bounce(const Vector3 &p_normal) const;
	_FORCE_INLINE_ Vector3 reflect(const Vector3 &p_normal) const;

	/* Operators */

	_FORCE_INLINE_ Vector3 &operator+=(const Vector3 &p_v);
	_FORCE_INLINE_ Vector3 operator+(const Vector3 &p_v) const;
	_FORCE_INLINE_ Vector3 &operator-=(const Vector3 &p_v);
	_FORCE_INLINE_ Vector3 operator-(const Vector3 &p_v) const;
	_FORCE_INLINE_ Vector3 &operator*=(const Vector3 &p_v);
	_FORCE_INLINE_ Vector3 operator*(const Vector3 &p_v) const;
	_FORCE_INLINE_ Vector3 &operator/=(const Vector3 &p_v);
	_FORCE_INLINE_ Vector3 operator/(const Vector3 &p_v) const;

	_FORCE_INLINE_ Vector3 &operator*=(real_t p_scalar);
	_FORCE_INLINE_ Vector3 operator*(real_t p_scalar) const;
	_FORCE_INLINE_ Vector3 &operator/=(real_t p_scalar);
	_FORCE_INLINE_ Vector3 operator/(real_t p_scalar) const;

	_FORCE_INLINE_ Vector3 operator-() const;

	_FORCE_INLINE_ bool operator==(const Vector3 &p_v) const;
	_FORCE_INLINE_ bool operator!=(const Vector3 &p_v) const;
	_FORCE_INLINE_ bool operator<(const Vector3 &p_v) const;
	_FORCE_INLINE_ bool operator<=(const Vector3 &p_v) const;
	_FORCE_INLINE_ bool operator>(const Vector3 &p_v) const;
	_FORCE_INLINE_ bool operator>=(const Vector3 &p_v) const;

	operator String() const;

	_FORCE_INLINE_ Vector3(real_t p_x, real_t p_y, real_t p_z) {
		x = p_x;
		y = p_y;
		z = p_z;
	}
	_FORCE_INLINE_ Vector3() { x = y = z = 0; }
};

// Should be included after class definition, otherwise we get circular refs
#include "basis.h"

Vector3 Vector3::cross(const Vector3 &p_b) const {

	Vector3 ret(
			(y * p_b.z) - (z * p_b.y),
			(z * p_b.x) - (x * p_b.z),
			(x * p_b.y) - (y * p_b.x));

	return ret;
}

real_t Vector3::dot(const Vector3 &p_b) const {

	return x * p_b.x + y * p_b.y + z * p_b.z;
}

Basis Vector3::outer(const Vector3 &p_b) const {

	Vector3 row0(x * p_b.x, x * p_b.y, x * p_b.z);
	Vector3 row1(y * p_b.x, y * p_b.y, y * p_b.z);
	Vector3 row2(z * p_b.x, z * p_b.y, z * p_b.z);

	return Basis(row0, row1, row2);
}

Basis Vector3::to_diagonal_matrix() const {
	return Basis(x, 0, 0,
			0, y, 0,
			0, 0, z);
}

Vector3 Vector3::abs() const {

	return Vector3(Math::abs(x), Math::abs(y), Math::abs(z));
}

Vector3 Vector3::sign() const {

	return Vector3(SGN(x), SGN(y), SGN(z));
}

Vector3 Vector3::floor() const {

	return Vector3(Math::floor(x), Math::floor(y), Math::floor(z));
}

Vector3 Vector3::ceil() const {

	return Vector3(Math::ceil(x), Math::ceil(y), Math::ceil(z));
}

Vector3 Vector3::round() const {

	return Vector3(Math::round(x), Math::round(y), Math::round(z));
}

Vector3 Vector3::linear_interpolate(const Vector3 &p_b, real_t p_t) const {

	return Vector3(
			x + (p_t * (p_b.x - x)),
			y + (p_t * (p_b.y - y)),
			z + (p_t * (p_b.z - z)));
}

Vector3 Vector3::slerp(const Vector3 &p_b, real_t p_t) const {
	real_t theta = angle_to(p_b);
	return rotated(cross(p_b).normalized(), theta * p_t);
}

real_t Vector3::distance_to(const Vector3 &p_b) const {

	return (p_b - *this).length();
}

real_t Vector3::distance_squared_to(const Vector3 &p_b) const {

	return (p_b - *this).length_squared();
}

Vector3 Vector3::posmod(const real_t p_mod) const {
	return Vector3(Math::fposmod(x, p_mod), Math::fposmod(y, p_mod), Math::fposmod(z, p_mod));
}

Vector3 Vector3::posmodv(const Vector3 &p_modv) const {
	return Vector3(Math::fposmod(x, p_modv.x), Math::fposmod(y, p_modv.y), Math::fposmod(z, p_modv.z));
}

Vector3 Vector3::project(const Vector3 &p_b) const {
	return p_b * (dot(p_b) / p_b.length_squared());
}

real_t Vector3::angle_to(const Vector3 &p_b) const {

	return Math::atan2(cross(p_b).length(), dot(p_b));
}

Vector3 Vector3::direction_to(const Vector3 &p_b) const {
	Vector3 ret(p_b.x - x, p_b.y - y, p_b.z - z);
	ret.normalize();
	return ret;
}

/* Operators */

Vector3 &Vector3::operator+=(const Vector3 &p_v) {

	x += p_v.x;
	y += p_v.y;
	z += p_v.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3 &p_v) const {

	return Vector3(x + p_v.x, y + p_v.y, z + p_v.z);
}

Vector3 &Vector3::operator-=(const Vector3 &p_v) {

	x -= p_v.x;
	y -= p_v.y;
	z -= p_v.z;
	return *this;
}
Vector3 Vector3::operator-(const Vector3 &p_v) const {

	return Vector3(x - p_v.x, y - p_v.y, z - p_v.z);
}

Vector3 &Vector3::operator*=(const Vector3 &p_v) {

	x *= p_v.x;
	y *= p_v.y;
	z *= p_v.z;
	return *this;
}
Vector3 Vector3::operator*(const Vector3 &p_v) const {

	return Vector3(x * p_v.x, y * p_v.y, z * p_v.z);
}

Vector3 &Vector3::operator/=(const Vector3 &p_v) {

	x /= p_v.x;
	y /= p_v.y;
	z /= p_v.z;
	return *this;
}

Vector3 Vector3::operator/(const Vector3 &p_v) const {

	return Vector3(x / p_v.x, y / p_v.y, z / p_v.z);
}

Vector3 &Vector3::operator*=(real_t p_scalar) {

	x *= p_scalar;
	y *= p_scalar;
	z *= p_scalar;
	return *this;
}

_FORCE_INLINE_ Vector3 operator*(real_t p_scalar, const Vector3 &p_vec) {

	return p_vec * p_scalar;
}

Vector3 Vector3::operator*(real_t p_scalar) const {

	return Vector3(x * p_scalar, y * p_scalar, z * p_scalar);
}

Vector3 &Vector3::operator/=(real_t p_scalar) {

	x /= p_scalar;
	y /= p_scalar;
	z /= p_scalar;
	return *this;
}

Vector3 Vector3::operator/(real_t p_scalar) const {

	return Vector3(x / p_scalar, y / p_scalar, z / p_scalar);
}

Vector3 Vector3::operator-() const {

	return Vector3(-x, -y, -z);
}

bool Vector3::operator==(const Vector3 &p_v) const {

	return (Math::is_equal_approx(x, p_v.x) && Math::is_equal_approx(y, p_v.y) && Math::is_equal_approx(z, p_v.z));
}

bool Vector3::operator!=(const Vector3 &p_v) const {
	return (!Math::is_equal_approx(x, p_v.x) || !Math::is_equal_approx(y, p_v.y) || !Math::is_equal_approx(z, p_v.z));
}

bool Vector3::operator<(const Vector3 &p_v) const {

	if (Math::is_equal_approx(x, p_v.x)) {
		if (Math::is_equal_approx(y, p_v.y))
			return z < p_v.z;
		else
			return y < p_v.y;
	} else {
		return x < p_v.x;
	}
}

bool Vector3::operator>(const Vector3 &p_v) const {

	if (x == p_v.x) {
		if (y == p_v.y)
			return z > p_v.z;
		else
			return y > p_v.y;
	} else {
		return x > p_v.x;
	}
}

bool Vector3::operator<=(const Vector3 &p_v) const {

	if (Math::is_equal_approx(x, p_v.x)) {
		if (Math::is_equal_approx(y, p_v.y))
			return z <= p_v.z;
		else
			return y < p_v.y;
	} else {
		return x < p_v.x;
	}
}

bool Vector3::operator>=(const Vector3 &p_v) const {

	if (x == p_v.x) {
		if (y == p_v.y)
			return z >= p_v.z;
		else
			return y > p_v.y;
	} else {
		return x > p_v.x;
	}
}

_FORCE_INLINE_ Vector3 vec3_cross(const Vector3 &p_a, const Vector3 &p_b) {

	return p_a.cross(p_b);
}

_FORCE_INLINE_ real_t vec3_dot(const Vector3 &p_a, const Vector3 &p_b) {

	return p_a.dot(p_b);
}

real_t Vector3::length() const {

	real_t x2 = x * x;
	real_t y2 = y * y;
	real_t z2 = z * z;

	return Math::sqrt(x2 + y2 + z2);
}

real_t Vector3::length_squared() const {

	real_t x2 = x * x;
	real_t y2 = y * y;
	real_t z2 = z * z;

	return x2 + y2 + z2;
}

void Vector3::normalize() {

	real_t lengthsq = length_squared();
	if (lengthsq == 0) {
		x = y = z = 0;
	} else {
		real_t length = Math::sqrt(lengthsq);
		x /= length;
		y /= length;
		z /= length;
	}
}

Vector3 Vector3::normalized() const {

	Vector3 v = *this;
	v.normalize();
	return v;
}

bool Vector3::is_normalized() const {
	// use length_squared() instead of length() to avoid sqrt(), makes it more stringent.
	return Math::is_equal_approx(length_squared(), 1.0, UNIT_EPSILON);
}

Vector3 Vector3::inverse() const {

	return Vector3(1.0 / x, 1.0 / y, 1.0 / z);
}

void Vector3::zero() {

	x = y = z = 0;
}

// slide returns the component of the vector along the given plane, specified by its normal vector.
Vector3 Vector3::slide(const Vector3 &p_normal) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V(!p_normal.is_normalized(), Vector3());
#endif
	return *this - p_normal * this->dot(p_normal);
}

Vector3 Vector3::bounce(const Vector3 &p_normal) const {
	return -reflect(p_normal);
}

Vector3 Vector3::reflect(const Vector3 &p_normal) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V(!p_normal.is_normalized(), Vector3());
#endif
	return 2.0 * p_normal * this->dot(p_normal) - *this;
}

#endif // VECTOR3_H
