#pragma once

// std
#include <cmath>
#include <type_traits>

namespace glue
{
	struct vec3
	{
		float x;
		float y;
		float z;

		inline constexpr vec3(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f) : x(x), y(y), z(z) {}
		inline constexpr vec3(const int x, const int y, const int z) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)) {}

		template <typename T>
		inline constexpr vec3(T x, T y, T z)
		{
			static_assert(std::is_arithmetic<T>::value, "non-numeric type provided");
			this->x = static_cast<float>(x);
        		this->y = static_cast<float>(y);
        		this->z = static_cast<float>(z);
		}

		inline constexpr vec3 operator+(const vec3 &v) const
		{
			return vec3(x + v.x, y + v.y, z + v.y);
		}

		inline constexpr vec3 operator-(const vec3 &v) const
		{
			return vec3(x - v.x, y - v.y, z - v.z);
		}

		inline constexpr vec3 operator*(const vec3 &v) const
		{
			return vec3(x * v.x, y * v.y, z * v.z);
		}

		template <typename T>
		inline constexpr vec3 operator*(const T s) const
		{
			static_assert(std::is_arithmetic<T>::value, "non-numeric type provided");
			return vec3(x * s, y * s, z * s);
		}

		inline constexpr vec3 operator/(const vec3 &v) const
		{
			return vec3(x / v.x, y / v.y, z / v.z);
		}

		template <typename T>
		inline constexpr vec3 operator/(const T s) const
		{
			static_assert(std::is_arithmetic<T>::value, "non-numeric type provided");
			return vec3(x / s, y / s, z / s);
		}

#if __cplusplus >= 202002L
		inline constexpr float length() const
#else
		float length() const
#endif
		{
			return std::sqrt(x * x + y * y + z * z);
		}

#if __cplusplus >= 202002L
		inline constexpr vec3 norm() const
#else
		vec3 norm() const
#endif
		{
			float l = length();
			return *this / l;
		}
	};
}