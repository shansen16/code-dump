#include "Vertex.h"



void Vertex::Draw(Shader& shader, glm::mat4 cameraMatrix)
{
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "aPosition"), position.x, position.y, position.z);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	glUniform3f(glGetUniformLocation(shader.ID, "colour"), displayColour.x, displayColour.y, displayColour.z);
	glUniform2f(glGetUniformLocation(shader.ID, "u_resolution"), 800.0f, 800.0f);
}
