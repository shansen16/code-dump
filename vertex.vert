#version 330 core


out vec4 colour;
out vec4 position;

uniform vec3 aPosition;
uniform mat4 camMatrix;
uniform vec3 aColour;


// Outputs the colour for the Fragment Shader

void main()
{
	position = camMatrix * vec4(aPosition, 1.0);

	colour =  vec4(aColour, 1.0);
}
