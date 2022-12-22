#include"Camera.h"



Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position =  position;
	distanceFromTarget = glm::length(Position);
	orientation = Position - target;
	right = glm::normalize(glm::cross(up, orientation));
	cameraUp = glm::normalize(glm::cross(orientation, right));
}

glm::vec2 Camera::getCursorPos(GLFWwindow* window)
{
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	x =  2 * x / width -1;
	y = 1- 2 * y / height ;
	return glm::vec2(x, y);
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	
	orientation = Position - target;
	right = glm::normalize(glm::cross(up, orientation));
	cameraUp = glm::normalize(glm::cross(orientation, right));
	view = glm::lookAt(Position, target, up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));

}


void Camera::Inputs(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
		{
			currentCoords = getCursorPos(window);
			if (firstClick)
			{
				mouseDirection = glm::vec2(0, 0);
				firstClick = false;
			}
			else 
			{
				mouseDirection = PreviousCoords - currentCoords;
			}

			Position += mouseDirection.x * right * sensitivity;
			Position += mouseDirection.y * cameraUp * sensitivity;

			target += mouseDirection.x * right * sensitivity;
			target += mouseDirection.y * cameraUp * sensitivity;
			PreviousCoords = currentCoords;
		}
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
		glm::vec2 currentMousePos;
		if (firstClick)
		{
			PreviousCoords = getCursorPos(window);
			firstClick = false;
		}
		currentMousePos = getCursorPos(window);
		glm::vec2 mouseMovement = currentMousePos - PreviousCoords;
		glm::vec3 threeDMouseDirection = mouseDirection.x * right + mouseDirection.y * cameraUp;
		glm::vec3 rotationAxis = glm::cross(threeDMouseDirection, orientation);
		glm::vec3 centeredPos = Position - target;
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(sensitivity * glm::length(mouseDirection)), rotationAxis);
		centeredPos = glm::vec3(rotation * glm::vec4(centeredPos, 0));
		Position = centeredPos + target;
		currentCoords = getCursorPos(window);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
	{
		firstClick = false;
	}

	

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		glm::vec3 centeredPos = Position - target;
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(-speed), right);
		centeredPos = glm::vec3(rotation * glm::vec4(centeredPos, 0));
		Position = centeredPos + target;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		glm::vec3 centeredPos = Position - target;
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(speed), right);
		centeredPos = glm::vec3(rotation * glm::vec4(centeredPos, 0));
		Position = centeredPos + target;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		glm::vec3 centeredPos = Position - target;
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(speed), cameraUp);
		centeredPos = glm::vec3(rotation * glm::vec4(centeredPos, 0));
		Position = centeredPos + target;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		glm::vec3 centeredPos = Position - target;
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(-speed), cameraUp);
		centeredPos = glm::vec3(rotation * glm::vec4(centeredPos, 0));
		Position = centeredPos + target;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glm::vec3 centeredPos = Position - target;
		centeredPos -= (1 / (20 * speed)) * orientation;
		distanceFromTarget = glm::length(centeredPos);
		Position = centeredPos + target;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		glm::vec3 centeredPos = Position - target;
		centeredPos += (1 /(20 * speed)) * orientation;
		distanceFromTarget = glm::length(centeredPos);
		Position = centeredPos + target;
	}



	//autmoatic camera placement code
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		orientation = glm::vec3(-1.0f, 0.0f, 0.0f);
		Position = glm::vec3(distanceFromTarget, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		orientation = glm::vec3(0.0f, -1.0f, 0.0f);
		Position = glm::vec3(0.0f, distanceFromTarget, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		Position = glm::vec3(0.0f, 0.0f, distanceFromTarget);
	}
}