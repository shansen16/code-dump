#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include<math.h>

#include "VAO.h"

const double pi = 3.14159265358979323846;

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	float distanceFromTarget;
	glm::vec3 orientation;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraUp;
	glm::vec3 right;
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	bool firstClick = true;
	bool printed = false; //delete later

	int width;
	int height;

	float speed = 1.0f;
	float sensitivity = 1.0f;
		
	glm::vec2 PreviousCoords;
	glm::vec2 mouseDirection;
	glm::vec2 currentCoords;

	Camera(int width, int height, glm::vec3 position);
	glm::vec2 getCursorPos(GLFWwindow* window);
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	
	void Inputs(GLFWwindow* window);

};

#endif
