#pragma once

// std
#include <cmath>
#include <type_traits>

namespace glue
{
	struct vec2
	{
		float x, y;

		constexpr vec2(const float x = 0.0f, const float y = 0.0f) : x(x), y(y) {}
		constexpr vec2(const int x, const int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}

		template <typename T>
		constexpr vec2(T x, T y)
		{
			static_assert(std::is_arithmetic<T>::value, "non-numeric type provided");
			this->x = static_cast<float>(x);
        		this->y = static_cast<float>(y);
		}

		constexpr vec2 operator+(const vec2 &v) const
		{
			return vec2(x + v.x, y + v.y);
		}

		constexpr vec2 operator-(const vec2 &v) const
		{
			return vec2(x - v.x, y - v.y);
		}

		constexpr vec2 operator*(const vec2 &v) const
		{
			return vec2(x * v.x, y * v.y);
		}

		template <typename T>
		constexpr vec2 operator*(const T s) const
		{
			static_assert(std::is_arithmetic<T>::value, "non-numeric type provided");
			return vec2(x * s, y * s);
		}

		constexpr vec2 operator/(const vec2 &v) const
		{
			return vec2(x / v.x, y / v.y);
		}

		template <typename T>
		constexpr vec2 operator/(const T s) const
		{
			static_assert(std::is_arithmetic<T>::value, "non-numeric type provided");
			return vec2(x / s, y / s);
		}

#if __cplusplus >= 202002L
		constexpr float length() const
#else
		float length() const
#endif
		{
			return std::sqrt(x * x + y * y);
		}

#if __cplusplus >= 202002L
		constexpr vec2 norm() const
#else
		vec2 norm() const
#endif
		{
			float l = length();
			return *this / l;
		}
	};
}