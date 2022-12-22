#include "shaderClass.h"


//reads text file and outputs a single string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader()
{

}
//Constructor function to build from two different shaders(vertex and fragment)
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into c style strings
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// attach vertex shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	//checks if vertex shader has compiled correctly
	compileErrors(vertexShader, "VERTEX");


	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// attach fragment shader source to the fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//complule fragment shader into machine code
	//checks if fragment shader has compiled correctly
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");


	//creates shader program object and get its reference
	ID = glCreateProgram();

	//attach the vertex and fragment shaders to shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	//link up all the shaders together into the shader program
	glLinkProgram(ID);
	//checks if shaders have linked correctly
	compileErrors(ID, "PROGRAM");


	//delete the now useless objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}
//Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}
//Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

//checks if the different sahders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type) 
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) 
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for " << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for " << type << "\n" << std::endl;
		}
	}
}