#pragma once

#ifndef GLUE_MAT4_TYPE
#include "./base/type_mat4.hpp"
#endif

namespace glue
{
#ifdef GLUE_MAT4_TYPE
	using mat4 = GLUE_MAT4_TYPE;
#endif
}