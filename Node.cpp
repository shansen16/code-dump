#include "Node.h"

Node::Node()
{

}

Node::Node(glm::vec2 position, int sides, float radius)
{
	centrePos = position;
	Node::shaderProgram = Shader("vertex.vert", "face.frag");
	std::vector <glm::vec3> points;
	points.push_back(glm::vec3(position, 0));
	for (int i = 1; i < sides; i++)
	{
		points.push_back((glm::vec3(radius * cos((1 - i) * 2 * pi / sides), radius * sin((1 - i) * 2 * pi / sides), 0)) + glm::vec3(position, 0));
	}
	std::vector <GLuint> indices;
	for (int i = 0; i < sides - 1; i++)
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	indices.push_back(0);
	indices.push_back(sides);
	indices.push_back(1);
	Node::points = points;
	Node::indices = indices;

	VAO.Bind();

	VBO VBOPoints(points);
	//VBO VBOColour(glm::vec3(0.0f, 0.0f, 0.0f));
	EBO EBO(indices);

	VAO.LinkAttrib(VBOPoints, 0, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);
	//VAO.LinkAttrib(VBOColour, 1, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);

	VAO.Unbind();
	VBOPoints.Unbind();
	//VBOColour.Unbind();
	EBO.Unbind();

	EBO.Delete();
	VBOPoints.Delete();
}
void Node::Draw()
{

	shaderProgram.Activate();
	// Bind the VAO so OpenGL knows to use it
	VAO.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	VAO.Unbind();
}