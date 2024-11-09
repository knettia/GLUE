#pragma once

// std
#include <cmath>
#include <limits>
#include <type_traits>

namespace glue
{
	struct unsigned_float
	{
		float value;

		inline constexpr unsigned_float(float val = 0.0f) : value((val < 0.0f) ? 0.0f : val) {}

		inline constexpr operator float() const { return value; }

		template <typename _T>
		inline constexpr unsigned_float &operator=(const _T &val)
		{
			static_assert(std::is_arithmetic<_T>::value, "non-numeric type provided");
			value = (val < 0.0f) ? 0.0f : static_cast<float>(val);
			return *this;
		}

		template <typename _T>
		inline constexpr float operator+(const _T &val) const
		{
			static_assert(std::is_arithmetic<_T>::value, "non-numeric type provided");
			return value + static_cast<float>(val);
		}

		template <typename _T>
		inline constexpr float operator-(const _T &val) const
		{
			static_assert(std::is_arithmetic<_T>::value, "non-numeric type provided");
			return value - static_cast<float>(val);
		}

		template <typename _T>
		inline constexpr float operator*(const _T &val) const
		{
			static_assert(std::is_arithmetic<_T>::value, "non-numeric type provided");
			return value * static_cast<float>(val);
		}

		template <typename _T>
		inline constexpr float operator/(const _T &val) const
		{
			static_assert(std::is_arithmetic<_T>::value, "non-numeric type provided");
			if (val == 0)
				return std::numeric_limits<float>::infinity();
			return value / static_cast<float>(val);
		}

		template <typename _T>
		inline constexpr float operator^(const _T &val) const
		{
			static_assert(std::is_arithmetic<_T>::value, "non-numeric type provided");
			return std::pow(value, static_cast<float>(val));
		}
	};
}