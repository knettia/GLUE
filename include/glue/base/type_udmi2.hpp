#pragma once

namespace glue
{
	struct udmi2
	{
		vec2 norm, abs;

		udmi2(const vec2 &norm = vec2(0.0f, 0.0f), const vec2 &abs = vec2(0.0f, 0.0f)) : norm(norm), abs(abs) {}
	};
}