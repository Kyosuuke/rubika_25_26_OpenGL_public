#include "Threshold.h"
#include "Shader.h"

#include <cstddef>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace threshold
{
	float vertices[] =
	{
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] =
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	
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
	
	void init()
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		shader.InitShader("Ressources/VertexShader.glsl", "Ressources/FragmentShader.glsl");
	}

	void update()
	{
		// Update threshold value
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		
	}

	void draw()
	{
		shader.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void destroy()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(shaderProgram);
	}
}
