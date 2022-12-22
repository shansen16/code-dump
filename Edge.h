#pragma once

#ifndef EDGE_CLASS_H
#define MESH_CLASS_H

#include "Node.h"

class Edge
{
public:
	VAO VAO;
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	Vertex start;
	Vertex end;
	glm::vec3 colour = glm::vec3(0.0f, 0.0f, 0.0f);
	Edge(Vertex start, Vertex end);
	void Draw(Camera& camera, Shader& shader);
	void findTwoPerpendicularVectors(glm::vec3 direction, glm::vec3& overwriteOne, glm::vec3& overwriteTwo);
};

#endif