//vertex array object
#include"VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

//links a VBO attribute to the VAO using a specific layout
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)  //example of arguments:VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float))
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}