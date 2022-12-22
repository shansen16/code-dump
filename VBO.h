//vertex buffer object
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "Vertex.h"


class VBO 
{
	public:
		//reference ID of the VBO
		GLuint ID;
		//Constructor function 
		VBO(std::vector <Vertex>& vertices);
		VBO(std::vector <glm::vec3> points);
		VBO(glm::vec3 colour);

		void Bind();
		void Unbind();
		void Delete();
};
#endif // !VBO_CLASS_H
