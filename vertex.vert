#version 330 core

out vec2 fragPos;


uniform mat4 translation;


// Outputs the colour for the Fragment Shader

void main()
{
	vec2 pointPos = vec2(translation[3][0], translation[3][1]);
	fragPos = pointPos;
	aColour = vec4(0.0, 0.0, 0.0, 0.0);
	uResolution = resolution;
}
