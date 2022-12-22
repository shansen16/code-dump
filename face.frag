#version 330 core

//inputs the colour from the Vertex Shader
in vec3 colour;

void main()
{
	gl_FragColor = vec4(colour, 1.0f);
}