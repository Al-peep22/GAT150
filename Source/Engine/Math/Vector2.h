#pragma once
#include "Math.h"
#include <cassert>
#include <iostream>

namespace viper {
	template<typename T>

	struct Vector2 {
		union {
			struct { T x, y; };
			struct { T u, v; };
		};

		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }

		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

		Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
		Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
		Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
		Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

		Vector2& operator += (float s) { x += s; y += s; return *this; }
		Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
		Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

		//square root (x * x + y * y)

		/// <summary>
		/// Calculates the squared length of a 2D vector.
		/// </summary>
		/// <returns>The sum of the squares of the x and y components.</returns>
		float LengthSquare() const { return (x * x) + (y * y); }

		/// <summary>
		/// Calculates the length (magnitude) of the object.
		/// </summary>
		/// <returns>The length as a floating-point value.</returns>
		float Length() const { return viper::math::sqrtf(LengthSquare()); }

		/// <summary>
		/// Returns a normalized (unit length) version of the vector.
		/// </summary>
		/// <returns>A Vector2 representing the original vector scaled to have a length of 1.</returns>
		Vector2 Normalized() const { return *this / Length(); }

		/// <summary>
		/// Returns the angle, in radians, between the positive x-axis and the point (x, y).
		/// </summary>
		/// <returns>The angle in radians, computed using atan2f(y, x).</returns>
		float Angle() const { return viper::math::atan2f(y, x); };

		/// <summary>
		/// Returns a new vector that is the result of rotating this vector by the specified angle in radians.
		/// </summary>
		/// <param name="radians">The angle to rotate the vector, in radians.</param>
		/// <returns>A Vector2 representing the rotated vector.</returns>
		Vector2 Rotate(float radians) const {
			Vector2 v;

			v.x = x * viper::math::cosf(radians) - y * viper::math::sinf(radians);
			v.y = x * viper::math::sinf(radians) + y * viper::math::cosf(radians);

			return v;
		}

		/// <summary>
		/// Calculates the dot product of two 2D vectors.
		/// </summary>
		/// <param name="a">The first vector operand.</param>
		/// <param name="b">The second vector operand.</param>
		/// <returns>The dot product of the two vectors as a float.</returns>
		static float Dot(const Vector2& a, const Vector2& b) {
			return a.x * b.x + a.y * b.y;
		}

		/// <summary>
		/// Calculates the 2D cross product of two vectors.
		/// </summary>
		/// <param name="a">The first vector operand.</param>
		/// <param name="b">The second vector operand.</param>
		/// <returns>The scalar value of the cross product (a.x * b.y - a.y * b.x).</returns>
		static float Cross(const Vector2& a, const Vector2& b) {
			return a.x * b.y - a.y * b.x;
		}

		/// <summary>
		/// Calculates the angle in radians between two 2D vectors.
		/// </summary>
		/// <param name="a">The first vector.</param>
		/// <param name="b">The second vector.</param>
		/// <returns>The angle in radians between vector a and vector b.</returns>
		static float AngleBetween(const Vector2& a, const Vector2& b) {
			return math::acosf(Dot(a, b));
		}

		/// <summary>
		/// Calculates the signed angle in radians between two 2D vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The signed angle in radians between vector a and vector b. The sign indicates the direction from a to b.</returns>
		static float SignedAngleBetween(const Vector2& a, const Vector2& b) {
			float x = Dot(a, b);
			float y = Cross(a, b);

			return math::atan2f(y, x);
		}
	};

	/// <summary>
	/// Outputs a Vector2 object to a stream in the format {x, y}.
	/// </summary>
	/// <typeparam name="T">The type of the Vector2 components.</typeparam>
	/// <param name="stream">The output stream to write to.</param>
	/// <param name="v">The Vector2 object to output.</param>
	/// <returns>A reference to the output stream after writing the Vector2.</returns>
	template <typename T>
	std::ostream& operator << (std::ostream& stream, const Vector2<T>& v) {
		stream << "{" << v.x << ", " << v.y << "}";
		return stream;
	}

	/// <summary>
	/// Extracts a Vector2<T> object from an input stream in the format { x, y }.
	/// </summary>
	/// <typeparam name="T">The type of the vector components (e.g., int, float, double).</typeparam>
	/// <param name="stream">The input stream to read from.</param>
	/// <param name="v">The Vector2<T> object to store the extracted values.</param>
	/// <returns>A reference to the input stream after extraction. Sets the stream's failbit if the input format is invalid.</returns>
	template <typename T>
	std::istream& operator >> (std::istream& stream, Vector2<T>& v) {
		char ch = '\0';

		// { x, y}

		// {
		if (!(stream >> std::ws >> ch) || ch != '{') {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// x
		if (!(stream >> std::ws >> v.x)) {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// ,
		if (!(stream >> std::ws >> ch) || ch != ',') {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// y
		if (!(stream >> std::ws >> v.y)) {
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

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}
