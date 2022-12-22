#include "Edge.h"


Edge::Edge(Vertex start, Vertex end)
{
	Edge::start = start;
	Edge::end = end;
	
	std::vector <Vertex> vertices;
	glm::vec3 direction = glm::normalize(end.position - start.position);
	glm::vec3 perpendicularX;
	glm::vec3 perpendicularY;

	findTwoPerpendicularVectors(direction, perpendicularX, perpendicularY);

	vertices.push_back(Vertex{ start.position + (perpendicularX + perpendicularY) * 0.001f, colour });
	vertices.push_back(Vertex{ start.position + (perpendicularX - perpendicularY) * 0.001f, colour });
	vertices.push_back(Vertex{ start.position + (-perpendicularX - perpendicularY) * 0.001f, colour });
	vertices.push_back(Vertex{ start.position + (-perpendicularX + perpendicularY) * 0.001f, colour });

	vertices.push_back(Vertex{ end.position + (perpendicularX + perpendicularY) * 0.001f, colour });
	vertices.push_back(Vertex{ end.position + (perpendicularX - perpendicularY) * 0.001f, colour });
	vertices.push_back(Vertex{ end.position + (-perpendicularX - perpendicularY) * 0.001f, colour });
	vertices.push_back(Vertex{ end.position + (-perpendicularX + perpendicularY) * 0.001f, colour });

	Edge::vertices = vertices;

	GLuint indices[] =
	{
		0, 4, 5,
		0, 4, 7,
		0, 3, 7,
		0, 1, 5,
		3, 2, 7,
		2, 6, 7,
		2 ,6, 5,
		1, 2, 5
	};
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	Edge::indices = ind;


	VAO.Bind();
	//Unbinds all objects to prevent accidentally modifying them
	VAO.Unbind();

}

void Edge::findTwoPerpendicularVectors(glm::vec3 direction, glm::vec3& overwriteOne, glm::vec3& overwriteTwo)
{
	if (direction == glm::vec3(1.0f, 0.0f, 0.0f))
	{
		overwriteOne = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
		overwriteTwo = glm::cross(direction, overwriteOne);
	}
	else
	{
		overwriteOne = glm::cross(direction, glm::vec3(1.0f, 0.0f, 0.0f));
		overwriteTwo = glm::cross(direction, overwriteOne);
	}
}


void Edge::Draw(Camera& camera, Shader& shader)
{
	shader.Activate();
	VAO.Bind();
	VBO VBO(vertices);
	//Generates Element Buffer Object and links it to vertices
	EBO EBO(indices);

	// Link VBO attributes such as coordinates and colours to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	VBO.Delete();
	EBO.Delete();
}