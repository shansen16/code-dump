//Element Buffer Object
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>

class EBO
{
public:
	//reference ID of the EBO
	GLuint ID;
	//Constructor function and binds to indices
	EBO(std::vector<GLuint>& indices);

	void Bind();
	void Unbind();
	void Delete();
};
#endif // !EBO_CLASS_H
