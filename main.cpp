//GLEW before GLFW, GLEW contains GL header so don't need to incude that.
#pragma comment (lib, "glew32s.lib")
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#define _USE_MATH_DEFINES //access math.h constants
#include <math.h>
#include "main.h"
#include "Utilities.h"
#include "Shader.h"


//global variables
const GLuint WIDTH = 800, HEIGHT = 600;
const std::string vertexShaderFilePath = "vs.glsl";
const std::string fragmentShaderFilePath = "fs.glsl";
float mixValue = 0.5f;

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
		//Position				//Color					//Texture
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,

		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		-0.5f, -0.4f,0.0f,		1.0f, 0.0f, 1.0f,		0.0f, 0.1f,
		0.4f, 0.5f, 0.0f,		1.0f, 1.0f, 0.0f,		0.9f, 1.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//GLfloat greenValue;
	//GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

	ourShader.Use();
	glUniform4f(glGetUniformLocation(ourShader.Program, "offset"), 0.0f, 0.0f, 0.0f, 0.0f);

	GLfloat texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	GLuint textures[2];
	glGenTextures(2, textures);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//if GL_CLAMP_TO_BORDER is used then we also need to specify the border color
	//float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, "container.jpg", textures[0]);
	bindTexture(GL_TEXTURE1, GL_TEXTURE_2D, "awesomeface.png", textures[1]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);


	//placeholder for checking time difference
	GLfloat previousTime = (GLfloat)glfwGetTime();
	//total time elapsed
	GLfloat totalTime = 0.0f;

	//3. Now draw the object
	//main loop
	while (!glfwWindowShouldClose(window))
	{
		//work out time difference since last frame
		GLfloat timeDiff = (GLfloat)glfwGetTime() - previousTime;
		totalTime += timeDiff;
		previousTime = (GLfloat)glfwGetTime();
		//check and call events
		glfwPollEvents();

		//do the rendering
		glClearColor(0.2f, 1.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//transformation
		glm::mat4 trans;
		trans = glm::rotate(trans, (GLfloat)M_PI * totalTime, glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::translate(trans, glm::vec3(0.5f, 0.0f, 0.0f));
		trans = glm::rotate(trans, -(GLfloat)M_PI * totalTime, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

		//2. Use our shader program when we want to render an object
		ourShader.Use();
		//updateColor(&greenValue);
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(ourShader.Program, "mixValue"), mixValue);

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
	//close the window upon ESC
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
	//change mixValue with arrows
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		mixValue += 0.1f;
		if (mixValue >= 1.0f) mixValue = 1.0f;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		mixValue -= 0.1f;
		if (mixValue <= 0.0f) mixValue = 0.0f;
	}
} 

void updateColor(GLfloat* greenColor){
	*greenColor = (sin(glfwGetTime())/2)+0.5;
}

void bindTexture(GLenum textureNumber, GLenum textureType, const char* texturePath, GLuint textureObject){
	int width, height;
	unsigned char* image;
	image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);

	glActiveTexture(textureNumber);
	glBindTexture(textureType, textureObject);
	glTexImage2D(textureType, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(textureType);
	SOIL_free_image_data(image);
	glBindTexture(textureType, 0);
}