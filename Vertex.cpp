#include "Vertex.h"



void Vertex::Draw(Shader& shader)
{
	shader.Activate();
	glm::mat4 translation = glm::mat4(1.0f);
	glm::translate(translation, glm::vec3(twoDPos, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(translation));
	glUniform3f(glGetUniformLocation(shader.ID, "colour"), displayColour.x, displayColour.y, displayColour.z);
	glUniform2f(glGetUniformLocation(shader.ID, "u_resolution"), 800.0f, 800.0f);
}
