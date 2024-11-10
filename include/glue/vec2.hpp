#pragma once

#ifndef GLUE_VEC2_TYPE
#include "./base/type_vec2.hpp"
#endif

namespace glue
{
#ifdef GLUE_VEC2_TYPE
	using vec2 = GLUE_VEC2_TYPE;
#endif
}