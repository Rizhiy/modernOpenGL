#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
public:
	GLuint Program;
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);
	void compileShader(GLuint Shader, const GLchar* filePath);
	void Use();
};

#endif