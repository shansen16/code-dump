#version 330 core
out vec4 FragColor;

//inputs the colour from the Vertex Shader
in vec3 colour;

void main()
{
	FragColor = vec4(colour, 1.0f);
}