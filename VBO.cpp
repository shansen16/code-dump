//vertex buffer object
#include"VBO.h"



//Constructor function 
VBO::VBO(std::vector <Vertex>& vertices)
{
	//generates a buffer object
	glGenBuffers(1, &ID);
	//binds it to the the array buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
}

VBO::VBO(std::vector <glm::vec3> points)
{
	glGenBuffers(1, &ID);
	//binds it to the the array buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_DYNAMIC_DRAW);
}

VBO::VBO(glm::vec3 colour)
{
	std::vector<glm::vec3> vectorColour;
	vectorColour.push_back(colour);
	glGenBuffers(1, &ID);
	//binds it to the the array buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vectorColour.size() * sizeof(glm::vec3), vectorColour.data(), GL_DYNAMIC_DRAW);
}

void VBO::Bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}