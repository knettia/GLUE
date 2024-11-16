#version 330 core
out vec4 fragColor;

uniform vec3 hue;      // the colour of the interface
uniform float opacity; // the opacity of the interface

void main()
{
	float alpha = 1.0 - clamp(opacity, 0.0, 1.0);

	fragColor = vec4(hue, alpha);
}