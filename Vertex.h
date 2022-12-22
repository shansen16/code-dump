#ifndef VERTEX_STRUCT_H
#define VERTEX_STRUCT_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glad/glad.h>
#include<vector>
#include <algorithm> 
#include "shaderClass.h"


struct Vertex
{
	glm::vec3 position;
	glm::vec3 colour;

	glm::vec3 displayColour = glm::vec3(0.0f, 0.0f, 0.0f);


	glm::vec2 twoDPos = glm::vec2(0.5f, 0.5f);
	bool selected;


	void Draw(Shader& shader, glm::mat4 cameraMatrix);
};

#endif VERTEX_STRUCT_H