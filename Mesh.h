#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include "Edge.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	glm::vec3 colour;
	VAO VAO;
	std::vector <Node> nodes;

	std::vector <Edge> edges;

	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, glm::vec3 colour, Shader& vertexShaderProgram);
	bool printed = false;
	bool editMode = false;

	void Draw(Camera& camera, Shader& shader);
	void DrawEditMode(Camera& camera, Shader& shader);
	//glm::vec2 getCursorPos(GLFWwindow* window);
	void Inputs(GLFWwindow* window, Camera camera);
	void EditInputs(GLFWwindow* window, Camera camera);
	void ObjectInputs(GLFWwindow* window, Camera camera);
	std::vector <int> selectedIndices;
	bool firstPress = true;
	glm::vec2 startMousePos;

	Shader vertexShaderProgram;
};


#endif
