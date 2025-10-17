#include "Threshold.h"
#include "Shader.h"
#include "Texture.h"

#include <cstddef>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex
{
	float position[3];
	float color[3];
	float texcoord[2];
};

namespace threshold
{
	Vertex vertices[] =
	{
		 { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

    { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    {  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },

    { 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },

    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },

    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }
	};

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};

	unsigned int indices[] =
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VBO;
	unsigned int VAO;
	//unsigned int EBO;
	
	// Shader
	unsigned int vertexShader;
	
	// Shader Debug
	int success;
	char infoLog[512];

	// Fragment Shader
	unsigned int fragmentShader;

	// Shader Program
	unsigned int shaderProgram;
	
	Shader shader = Shader();

	Texture texture1 = Texture();
	Texture texture2 = Texture();
	
	void init()
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		/*glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		*/
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		
		shader.InitShader("Ressources/VertexShader.glsl", "Ressources/FragmentShader.glsl");
		texture1.Init("../Resources/container.jpg");
		texture2.Init("../Resources/awesomeface.png");

		glEnable(GL_DEPTH_TEST);
	}

	void update()
	{
	}

	void draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();
		texture1.Use(&shader, 0);
		texture2.Use(&shader, 1);
		
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

		shader.SetMatrix("projection", projection);
		shader.SetMatrix("view", view);
		
		glBindVertexArray(VAO);

		for (unsigned int i = 0; i < 10; ++i)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.SetMatrix("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glBindVertexArray(0);
		
	}

	void destroy()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(shaderProgram);
	}
}
