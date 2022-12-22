#ifndef NODE_CLASS_H
#define NODE_CLASS_H

#include"EBO.h"
#include "Camera.h"




class Node
{
public:
	std::vector <glm::vec3> points;
	std::vector <GLuint> indices;


	Node();
	Node(glm::vec2 position, int sides, float radius);
	void Draw();
	VAO VAO;
	Shader shaderProgram;
	glm::vec2 centrePos;

};

#endif