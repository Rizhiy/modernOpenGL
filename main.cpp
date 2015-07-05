//GLEW before GLFW, GLEW contains GL header so don't need to incude that.
#pragma comment (lib, "glew32s.lib")
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "main.h"
#include "Utilities.h"
#include "Shader.h"

//global variables
const GLuint WIDTH = 800, HEIGHT = 600;
const std::string vertexShaderFilePath = "vs.glsl";
const std::string fragmentShaderFilePath = "fs.glsl";

int main(){

	//initialise GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//initialise GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//Creating window coordinates
	glViewport(0, 0, WIDTH, HEIGHT);
	
	Shader ourShader(vertexShaderFilePath.c_str(), fragmentShaderFilePath.c_str());

	glfwSetKeyCallback(window, key_callback);

	//triangle
	GLfloat vertices[] = {
		//Position      //Color
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.4f,0.0f,  1.0f, 0.0f, 1.0f,
		0.4f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f
	};

	//rectangle
	GLfloat vertices2[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};


	GLuint VBO, VAO, EBO;
	//Vertex Array Object
	glGenVertexArrays(1, &VAO);
	//Vertex Buffer
	glGenBuffers(1, &VBO);
	//Element Buffer Object
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//GLfloat greenValue;
	//GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

	GLint offsetLocation = glGetUniformLocation(ourShader.Program, "offset");
	ourShader.Use();
	glUniform4f(offsetLocation, 0.4f, 0.0f, 0.0f, 0.0f);
	//3. Now draw the object
	//main loop
	while (!glfwWindowShouldClose(window))
	{
		//check and call events
		glfwPollEvents();

		//do the rendering
		glClearColor(0.2f, 1.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//2. Use our shader program when we want to render an object
		ourShader.Use();
		//updateColor(&greenValue);
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		//3. Now draw the object
	
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	//cleanup after the end
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//terminate GLFW
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
} 

void updateColor(GLfloat* greenColor){
	*greenColor = (sin(glfwGetTime())/2)+0.5;
}