#version 330 core
in vec2 tex_coord;

out vec4 fragColor;

uniform sampler2D texture1;
uniform vec3 hue;
uniform float opacity;
uniform vec3 image_hue;
uniform float image_opacity;

void main()
{
	float interface_alpha = 1.0 - clamp(opacity, 0.0, 1.0);

	vec4 texture_colour = texture(texture1, tex_coord);
	texture_colour.rgb *= image_hue;

	float texture_alpha = 1.0 - clamp(image_opacity, 0.0, 1.0);
	texture_colour.a *= texture_alpha;

	float effective_alpha = texture_colour.a + interface_alpha * (1 - texture_colour.a);
	float r_result = texture_colour.r * texture_colour.a + hue.r * interface_alpha * (1 - texture_colour.a);
	float g_result = texture_colour.g * texture_colour.a + hue.g * interface_alpha * (1 - texture_colour.a);
	float b_result = texture_colour.b * texture_colour.a + hue.b * interface_alpha * (1 - texture_colour.a);

	fragColor = vec4(r_result, g_result, b_result, effective_alpha);
}