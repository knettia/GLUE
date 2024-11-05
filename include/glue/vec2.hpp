#pragma once

#include "./base/type_vec2.hpp"

namespace glue
{
#ifdef GLUE_VEC2_TYPE
	using data_vec2 = GLUE_VEC2_TYPE;
#else
	using data_vec2 = vec2;
#endif
}