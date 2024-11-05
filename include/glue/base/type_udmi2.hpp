#pragma once

#include "../vec2.hpp"

namespace glue
{
	struct udmi2
	{
		data_vec2 norm, abs;

		udmi2(const data_vec2 &norm = data_vec2(0.0f, 0.0f), const data_vec2 &abs = data_vec2(0.0f, 0.0f)) : norm(norm), abs(abs) {}
	};
}