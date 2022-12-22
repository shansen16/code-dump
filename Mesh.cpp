#include "Mesh.h"


Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, glm::vec3 colour, Shader& vertexShaderProgram)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::colour = colour;
	Mesh::vertexShaderProgram = vertexShaderProgram;

	VAO.Bind();

	//Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices);
	//Generates Element Buffer Object and links it to vertices
	EBO EBO(indices);

	// Link VBO attributes such as coordinates and colours to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	//Unbinds all objects to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	VBO.Delete();
	EBO.Delete();
}


void Mesh::Draw(Camera& camera, Shader& shader)
{
	
	shader.Activate();

	
	for (Vertex vert : vertices)
	{
		vert.Draw(vertexShaderProgram);
	}
	
	VAO.Bind();

	

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	

	VAO.Unbind();
	if (editMode)
	{
		DrawEditMode(camera, shader);
	}
	
}



void Mesh::DrawEditMode(Camera& camera, Shader& shader)
{




	//Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices);
	//Generates Element Buffer Object and links it to vertices
	EBO EBO(indices);

	// Link VBO attributes such as coordinates and colours to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	//Unbinds all objects to prevent accidentally modifying them

	VBO.Unbind();
	EBO.Unbind();

	VBO.Delete();
	EBO.Delete();


	edges.clear();
	for (int j = 0; j < indices.size(); j += 3)
	{
		edges.push_back(Edge(vertices[indices[j]], vertices[indices[j + 1]]));
		edges.push_back(Edge(vertices[indices[j + 1]], vertices[indices[j + 2]]));
		edges.push_back(Edge(vertices[indices[j + 2]], vertices[indices[j]]));
	}
	
	for (int i = 0; i < edges.size(); i++)
	{
		edges[i].Draw(camera, shader);
	}



	for (int i = 0; i < vertices.size(); i++)
	{
		Vertex activeVertex = vertices[i];
		glm::vec4 transformation = camera.cameraMatrix * glm::vec4(activeVertex.position, 1);
		glm::vec2 twoDTransform = glm::vec2(transformation.x / transformation.w, transformation.y / transformation.w);
		Node node(twoDTransform, 8, 0.01f);
		vertices[i].twoDPos = twoDTransform;
		node.Draw();
	}

}



void Mesh::EditInputs(GLFWwindow* window, Camera camera)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (!(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
		{
			selectedIndices.clear();
		}
		glm::vec2 location = camera.getCursorPos(window);
		int closestIndex = 0;
		float closest = 1.0f;
		if (firstPress)
		{

		}
		for (int i = 0; i < vertices.size(); i++)
		{
			float offset = glm::length(vertices[i].twoDPos - location);
			if (offset < 0.05f)
			{

				if (offset < closest)
				{

					vertices[i].selected = true;
					vertices[i].displayColour = glm::vec3(1.0f, 0.297101f, 0.019709f);
					vertices[closestIndex].selected = false;
					vertices[closestIndex].displayColour = glm::vec3(0.0f, 0.0f, 0.0f);
					closestIndex = i;
					closest = offset;
				}
			}
		}
		if (vertices[closestIndex].selected)
		{
			selectedIndices.push_back(closestIndex);
		}
		std::sort(selectedIndices.begin(), selectedIndices.end());
		selectedIndices.erase(std::unique(selectedIndices.begin(), selectedIndices.end()), selectedIndices.end());
	}

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		glm::vec2 currentMousePos;
		if (firstPress)
		{
			startMousePos = camera.getCursorPos(window);
			firstPress = false;
		}
		currentMousePos = camera.getCursorPos(window);
		glm::vec2 mouseMovement = currentMousePos - startMousePos;
		glm::vec3  translateVec = mouseMovement.x * camera.right + mouseMovement.y * camera.cameraUp;
		for (int i : selectedIndices)
		{
			vertices[i].position += sqrt(camera.distanceFromTarget) * translateVec;
		}

		startMousePos = currentMousePos;
	}
	else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE)
	{
		firstPress = true;
	}

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (firstPress)
		{
			editMode = false;
			firstPress = false;
		}
	}
}

void Mesh::ObjectInputs(GLFWwindow* window, Camera camera)
{
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (firstPress)
		{
			editMode = true;
			firstPress = false;
		}
		
	}
}

void Mesh::Inputs(GLFWwindow* window, Camera camera)
{
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
	{
		firstPress = false;
	}
	if (editMode)
	{
		EditInputs(window, camera);
	}
	else
	{
		ObjectInputs(window, camera);
	}
}