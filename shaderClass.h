#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);
class Shader 
{
	public:
		//reference ID of the Shader
		GLuint ID;
		//Constructor function to build from two different shaders(vertex and fragment)
		Shader();
		Shader(const char* vertexFile, const char* fragmentFile);

		//Activates the Shader Program
		void Activate();
		//Deletes the Shader Program
		void Delete();
	private:
		//checks if the different sahders have compiled properly
		void compileErrors(unsigned int shader, const char* type);
};



#endif