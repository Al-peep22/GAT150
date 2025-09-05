#pragma once

#include "Math/Vector2.h"
#include "Math/Math.h"

#include <iostream>
#include <random>

namespace viper::random {
    /// <summary>
    /// Returns a reference to a static Mersenne Twister random number generator.
    /// </summary>
    /// <returns>A reference to a static std::mt19937 random number generator instance.</returns>
    inline std::mt19937& generator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    /// <summary>
    /// Seeds the random number generator with the specified value.
    /// </summary>
    /// <param name="value">The seed value to initialize the random number generator.</param>
    inline void seed(unsigned int value) {
        generator().seed(value);
    }

    /// <summary>
    /// Generates a random integer within the specified range.
    /// </summary>
    /// <param name="min">The lower bound of the range (inclusive).</param>
    /// <param name="max">The upper bound of the range (inclusive).</param>
    /// <returns>A random integer between min and max, inclusive.</returns>
    inline int getInt(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);
        return dist(generator());
    }

    /// <summary>
    /// Returns a random integer in the range [0, max - 1].
    /// </summary>
    /// <param name="max">The exclusive upper bound for the random integer.</param>
    /// <returns>A random integer greater than or equal to 0 and less than max.</returns>
    inline int getInt(int max) {
        return getInt(0, max - 1);
    }

    /// <summary>
    /// Generates a random integer using a static uniform integer distribution.
    /// </summary>
    /// <returns>A randomly generated integer.</returns>
    inline int getInt() {
        static std::uniform_int_distribution<> dist;
        return dist(generator());
    }

    /// <summary>
    /// Generates a random real number within the specified range.
    /// </summary>
    /// <typeparam name="T">The floating-point type to use for the random number (defaults to float).</typeparam>
    /// <param name="min">The lower bound of the range (inclusive).</param>
    /// <param name="max">The upper bound of the range (exclusive).</param>
    /// <returns>A random real number of type T in the range [min, max).</returns>
    template <typename T = float>
    inline T getReal(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(generator());
    }

    /// <summary>
    /// Returns a random real number in the range [0, max].
    /// </summary>
    /// <typeparam name="T">The type of the real number to return. Defaults to float.</typeparam>
    /// <param name="max">The upper bound of the range for the random number.</param>
    /// <returns>A random real number of type T between 0 and max, inclusive.</returns>
    template <typename T = float>
    inline T getReal(T max) {
        return getReal(static_cast<T>(0), static_cast<T>(max));
    }

    /// <summary>
    /// Generates a random real number in the range [0, 1).
    /// </summary>
    /// <typeparam name="T">The floating-point type of the generated number. Defaults to float.</typeparam>
    /// <returns>A random real number of type T in the range [0, 1).</returns>
    template <typename T = float>
    inline T getReal() {
        static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
        return dist(generator());
    }

    /// <summary>
    /// Generates a random boolean value with equal probability for true or false.
    /// </summary>
    /// <returns>A boolean value, either true or false, chosen at random with a probability of 0.5 for each.</returns>
    inline bool getBool() {
        static std::bernoulli_distribution dist(0.5);
        return dist(generator());
    }

    /// <summary>
    /// Generates a 2D vector representing a point on the unit circle.
    /// </summary>
    /// <returns>A vec2 containing the x and y coordinates of a point on the unit circle.</returns>
    inline vec2 onUnitCircle() {
        float radians = getReal(math::twoPi);

        return { math::cosf(radians), math::sinf(radians) };
    }
}