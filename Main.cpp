#include"Mesh.h"


unsigned int screenWidth = 800;
unsigned int screenHeight = 800;
float clipStart = 0.01f;
float clipEnd = 100.0f;
glm::vec3 defaultColour = glm::vec3(0.8f, 0.8f, 0.8f);

Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /      
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), defaultColour},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), defaultColour},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), defaultColour},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), defaultColour}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};
Vertex cubeVertices[] =
{  //               COORDINATES           /            COLORS          /
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f), defaultColour},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), defaultColour},
	Vertex{glm::vec3( 0.1f, -0.1f, -0.1f), defaultColour},
	Vertex{glm::vec3( 0.1f, -0.1f,  0.1f), defaultColour},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f), defaultColour},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f), defaultColour},
	Vertex{glm::vec3( 0.1f,  0.1f, -0.1f), defaultColour},
	Vertex{glm::vec3( 0.1f,  0.1f,  0.1f), defaultColour},
};


GLuint cubeIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

std::vector <Mesh> SceneCollection;



int main() 
{
	
	
	
	glfwInit();

	//this is giving the window object the information it needs
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//tells GLFW to use CORE profile, therefore only modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //what version of openGL is being used

	//tells GLFW to use MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);


	//creates a window object. Or a pointer to a window object?
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL", NULL, NULL);
	
	

	if (window == NULL) 
	{ //error handling
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//I think this like sets it as the current window. Like the one the program uses
	glfwMakeContextCurrent(window);

	

	//loads GLAD so it configures OpenGL
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_MULTISAMPLE);

	//sets the start and end coordinates for the openGL rendering
	glViewport(0, 0, screenWidth, screenHeight);
	//sets a colour and nothing else
	
	//creates Shader object using shaders default.vert and face.frag
	Shader faceShaderProgram("face.vert", "face.frag");
	Shader vertexShaderProgram("vertex.vert", "vertex.frag");
	//Shader vertexShaderProgram("vertex.vert", "deafult.frag");

	//creation of axes
	//Edge xAxis(glm::vec3(clipEnd, 0.0f, 0.0f), glm::vec3(-clipEnd, 0.0f, 0.0f));
	//Edge yAxis(glm::vec3(0.0f, clipEnd, 0.0f), glm::vec3(0.0f, -clipEnd, 0.0f));
	//Edge zAxis(glm::vec3(0.0f, 0.0f, clipEnd), glm::vec3(0.0f, 0.0f, -clipEnd));

	//changing colour of axes
	//xAxis.colour = glm::vec3(0.8f, 0.0f, 0.0f);
	//yAxis.colour = glm::vec3(0.0f, 0.8f, 0.0f);
	//zAxis.colour = glm::vec3(0.0f, 0.0f, 0.8f);

	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	Mesh floor(verts, ind, defaultColour, vertexShaderProgram);
	SceneCollection.push_back(floor);

	

	std::vector <Vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
	std::vector <GLuint> cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
	Mesh cube(cubeVerts, cubeInd, defaultColour, vertexShaderProgram);
	SceneCollection.push_back(cube);

	glEnable(GL_DEPTH_TEST); //crucial piece of code. Goes more in depth in document. Needed to prevent overlapping and have the correct face of a mesh appears
	Node node(glm::vec2(0.0f, 0.0f), 8, 0.1f);
	Camera camera(screenWidth, screenHeight, glm::vec3(2.0f, 2.0f, 5.0f));

	//stops the window from closing immediately and for some subroutines to be 
	while (!glfwWindowShouldClose(window)) 
	{
		//xAxis.Draw(camera, faceShaderProgram);
		//yAxis.Draw(camera, faceShaderProgram);
		//zAxis.Draw(camera, faceShaderProgram);

		//specifies colour of background
		glClearColor(0.2f, 0.2f, 0.2, 1.0f);
		//clears the back buffer and assigns new colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //the GL_DEPTH_BUFFER_BIT solves the overlapping part
		//tells OpenGL what shader program to use

		


		camera.Inputs(window);
		camera.updateMatrix(45.0f, clipStart, clipEnd);

		camera.Matrix(faceShaderProgram, "camMatrix");

		floor.Inputs(window, camera);
		cube.Inputs(window, camera);
		
		floor.Draw(camera, faceShaderProgram);
		cube.Draw(camera, faceShaderProgram);

		//glUniform2f(glGetUniformLocation(vertexShaderProgram.ID, "pointPos"), 0.5f, 0.5f);
		//glUniform3f(glGetUniformLocation(vertexShaderProgram.ID, "colour"), 0.0f, 0.0f, 0.0f);
		//glUniform2f(glGetUniformLocation(vertexShaderProgram.ID, "resolution"), 800.0f, 800.0f);


		glfwSwapBuffers(window);

		//takes care of all GLFW events
		glfwPollEvents();
	}

	//delete all objects created
	
	faceShaderProgram.Delete();

	//terminating stuff
	glfwDestroyWindow(window);
	glfwTerminate();



	return 0;
}