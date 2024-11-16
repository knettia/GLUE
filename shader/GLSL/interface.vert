#version 330 core
layout (location = 0) in vec2 a_position;

out vec2 tex_coord; // for textured.frag

uniform vec2 screen_position;
uniform vec2 screen_size;
uniform vec2 reference;

vec2 offset_vertex(vec2 vextex_to_offset)
{
	float calculated_screen_x = (screen_position.x / reference.x) * 2.0 - 1.0;
	float calculated_screen_y = 1.0 - (screen_position.y / reference.y) * 2.0;

	float calculated_screen_width = (screen_size.x / reference.x) * 2.0;
	float calculated_screen_height = (screen_size.y / reference.y) * 2.0;

	vec2 vertex_position;
	if (vextex_to_offset == vec2(0.0, 0.0))
	{
		return vec2(calculated_screen_x, calculated_screen_y - calculated_screen_height);
	}
	else if (vextex_to_offset == vec2(1.0, 0.0))
	{
		return vec2(calculated_screen_x + calculated_screen_width, calculated_screen_y - calculated_screen_height);
	}
	else if (vextex_to_offset == vec2(1.0, 1.0))
	{
		return vec2(calculated_screen_x + calculated_screen_width, calculated_screen_y);
	}
	else // if (vextex_to_offset == vec2(0.0, 1.0))
	{
		return vec2(calculated_screen_x, calculated_screen_y);
	}

	// INTERAL ERROR
	return vextex_to_offset;
}

void main()
{
	gl_Position = vec4(offset_vertex(a_position), 0.0, 1.0);
	tex_coord = a_position;
}