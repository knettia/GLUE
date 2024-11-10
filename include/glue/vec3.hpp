#pragma once

#ifndef GLUE_VEC3_TYPE
#include "./base/type_vec3.hpp"
#endif

namespace glue
{
#ifdef GLUE_VEC3_TYPE
	using vec3 = GLUE_VEC3_TYPE;
#endif
}