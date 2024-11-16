#pragma once

// std
#include <cmath>

namespace glue
{
	struct mat4
	{
	private:
		float elements[4][4];
	public:
		constexpr mat4() noexcept
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					elements[i][j] = (i == j) ? 1.0f : 0.0f;
		}

		constexpr mat4(float m[4][4]) noexcept
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					elements[i][j] = m[i][j];
		}

		inline float* operator[](unsigned int index) noexcept
		{
			return elements[index];
		}

		inline const float* operator[](unsigned int index) const noexcept
		{
			return elements[index];
		}

		constexpr mat4 operator*(const mat4& m) const noexcept
		{
			mat4 result;
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
				{
					result[i][j] = 0;
					for (int k = 0; k < 4; ++k)
						result[i][j] += elements[i][k] * m[k][j];
				}
				
			return result;
		}
	};
}
