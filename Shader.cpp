#include <iostream>
#include "Shader.h"
#include "Utilities.h"

Shader::Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath)
{	
	this->Program = glCreateProgram();
	//shader compilation
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	compileShader(vertexShader, vertexSourcePath);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(fragmentShader, fragmentSourcePath);

	glAttachShader(this->Program, vertexShader);
	glAttachShader(this->Program, fragmentShader);
	glLinkProgram(this->Program);
	//check for success
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING FAILED!\n" << infoLog << std::endl;
	}
	//delete the shaders, free some memory
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::compileShader(GLuint Shader, const GLchar* filePath) {
	const GLchar* ShaderSource = readFile(filePath); //loads source
	glShaderSource(Shader, 1, &ShaderSource, NULL);
	glCompileShader(Shader);
	//check if compiled
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(Shader, 512, NULL, infoLog);
		GLint* type = 0;
		glGetShaderiv(Shader, GL_SHADER_TYPE, type);
		std::cout << "ERROR::SHADER::" << type << "::COMPILATION FAILED!\n" << infoLog << std::endl;
	}
}

void Shader::Use() {
	glUseProgram(this->Program);
}