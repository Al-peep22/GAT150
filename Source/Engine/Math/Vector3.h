#pragma once
#include "Math.h"
#include <cassert>
#include <iostream>

namespace viper {
	template<typename T>

	struct Vector3 {
		union {
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		Vector3() = default;
		Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}

		T operator [] (unsigned int index) const { assert(index < 3); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 3); return (&x)[index]; }

		Vector3 operator + (const Vector3& v) const { return Vector3{ x + v.x, y + v.y, z + v.z }; }
		Vector3 operator - (const Vector3& v) const { return Vector3{ x - v.x, y - v.y, z - v.z }; }
		Vector3 operator * (const Vector3& v) const { return Vector3{ x * v.x, y * v.y, z * v.z }; }
		Vector3 operator / (const Vector3& v) const { return Vector3{ x / v.x, y / v.y, z / v.z }; }

		Vector3 operator + (float s) const { return Vector3{ x + s, y + s, z + s }; }
		Vector3 operator - (float s) const { return Vector3{ x - s, y - s, z - s }; }
		Vector3 operator * (float s) const { return Vector3{ x * s, y * s, z * s }; }
		Vector3 operator / (float s) const { return Vector3{ x / s, y / s, z / s }; }

		Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

		Vector3& operator += (float s) { x += s; y += s; z += s; return *this; }
		Vector3& operator -= (float s) { x -= s; y -= s; z -= s; return *this; }
		Vector3& operator *= (float s) { x *= s; y *= s; z *= s; return *this; }
		Vector3& operator /= (float s) { x /= s; y /= s; z /= s; return *this; }

		//square root (x * x + y * y + z * z)

		/// <summary>
		/// Calculates the squared length (magnitude) of a 3D vector.
		/// </summary>
		/// <returns>The sum of the squares of the x, y, and z components of the vector.</returns>
		float LengthSquare() const { return (x * x) + (y * y) + (z * z); }

		/// <summary>
		/// Calculates the length (magnitude) of the object.
		/// </summary>
		/// <returns>The length as a floating-point value.</returns>
		float Length() const { return viper::math::sqrtf(LengthSquare()); }
	};

	/// <summary>
	/// Outputs a Vector3 object to a stream in the format {r, g, b}.
	/// </summary>
	/// <typeparam name="T">The type of the Vector3 components.</typeparam>
	/// <param name="stream">The output stream to write to.</param>
	/// <param name="v">The Vector3 object to output.</param>
	/// <returns>A reference to the output stream after writing the Vector3.</returns>
	template <typename T>
	std::ostream& operator << (std::ostream& stream, const Vector3<T>& v) {
		stream << "{" << v.r << ", " << v.g << ", " << v.b << "}";
		return stream;
	}

	/// <summary>
	/// Extracts a Vector3<T> object from an input stream in the format { r, g, b }. Sets the stream to fail state if the format is incorrect.
	/// </summary>
	/// <typeparam name="T">The type of the vector components (e.g., float, double, int).</typeparam>
	/// <param name="stream">The input stream to read from.</param>
	/// <param name="v">The Vector3<T> object to populate with the extracted values.</param>
	/// <returns>A reference to the input stream after extraction.</returns>
	template <typename T>
	std::istream& operator >> (std::istream& stream, Vector3<T>& v) {
		char ch = '\0';

		// { r, g, b}

		// {
		if (!(stream >> std::ws >> ch) || ch != '{') {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// r
		if (!(stream >> std::ws >> v.r)) {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// ,
		if (!(stream >> std::ws >> ch) || ch != ',') {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// g
		if (!(stream >> std::ws >> v.g)) {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// ,
		if (!(stream >> std::ws >> ch) || ch != ',') {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// b
		if (!(stream >> std::ws >> v.b)) {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// }
		if (!(stream >> std::ws >> ch) || ch != '}') {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		return stream;
	}

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}