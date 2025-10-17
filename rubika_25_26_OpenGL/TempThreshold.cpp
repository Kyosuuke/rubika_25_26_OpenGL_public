#include "TempThreshold.h"
#include "Shader.h"
#include "Texture.h"

#include <cstddef>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "TempShader.h"

struct Vertex
{
	float position[3];
	float color[3];
	float texcoord[2];
};

namespace TempThreshold
{
	Vertex vertices[] =
	{
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f },
   {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f },
   {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f },
   {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f },
   { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f },
   { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f },

   { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f },
   {  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f },
   {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f },
   {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f },
   { -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f },
   { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f },

   { -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f },
   { -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f },
   { -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f },
   { -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f },
   { -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f },
   { -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f },

   { 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f },
   { 0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f },
   { 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f },
   { 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f },
   { 0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f },
   { 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f },

   { -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f },
   {  0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f },
   {  0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f },
   {  0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f },
   { -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f },
   { -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f },

   { -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f },
   {  0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f },
   {  0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f },
   {  0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f },
   { -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f },
   { -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f }
	};

	unsigned int indices[] =
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VBO;
	unsigned int VAO;
	unsigned int lightVAO;
	
	// Shader
	unsigned int vertexShader;
	
	// Shader Debug
	int success;
	char infoLog[512];

	// Fragment Shader
	unsigned int fragmentShader;

	// Shader Program
	unsigned int shaderProgram;
	
	TempShader lightCubeShader = TempShader();
	TempShader lightShader = TempShader();

	Texture texture1 = Texture();
	Texture texture2 = Texture();

	static Camera camera = Camera();
	static bool firstMouse = true;
	static double lastX = 400.0;
	static double lastY = 300.0;

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	
	void init()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindVertexArray(VAO);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);

		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		
		lightCubeShader.InitShader("Ressources/TempVS.glsl", "Ressources/TempFS.glsl");
		lightShader.InitShader("Ressources/VS.glsl", "Ressources/FS.glsl");
		glEnable(GL_DEPTH_TEST);
	}

	void update()
	{
	}

	void draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Light cube
		
		lightShader.Use();
		
		float ambientIntensity = 0.2f + 0.1f * sinf((float)glfwGetTime());
		lightShader.SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		lightShader.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		lightShader.SetFloat("ambientStrength", ambientIntensity);
		lightShader.SetVec3("lightPos", lightPos);
		lightShader.SetVec3("viewPos", camera.GetPosition());

		glm::mat4 projection = glm::perspective(glm::radians(camera.GetFov()), (float)800 / 600, 0.1f, 100.0f);
		glm::mat4 view = camera.GetMatrix();
		lightShader.SetMatrix("projection", projection);
		lightShader.SetMatrix("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		lightShader.SetMatrix("model", model);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cube
		
		lightCubeShader.Use();

		lightCubeShader.SetMatrix("projection", projection);
		lightCubeShader.SetMatrix("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightCubeShader.SetMatrix("model", model);
		
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void destroy()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &lightVAO);
		glDeleteProgram(shaderProgram);
	}

	void ProcessMouse(double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
			return;
		}

		float xoffset = static_cast<float>(xpos - lastX);
		float yoffset = static_cast<float>(lastY - ypos); // reversed: y ranges bottom->top

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouse(xoffset, yoffset);
	}

	void ProcessScroll(double xoffset, double yoffset)
	{
		camera.ProcessMouseScroll(static_cast<float>(yoffset));
	}

	void ProcessKeyboardInput(float deltaTime)
	{
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(Camera::Direction::Forward, deltaTime * camera.GetCameraSpeed());
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(Camera::Direction::Backward, deltaTime * camera.GetCameraSpeed());
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(Camera::Direction::Left, deltaTime * camera.GetCameraSpeed());
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(Camera::Direction::Right, deltaTime * camera.GetCameraSpeed());
	}
}
