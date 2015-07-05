#include <string>

int main();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
char* readFile(std::string filePath);
void compileShader(GLuint Shader, std::string filePath, std::string shaderType);
void updateColor(GLfloat* greenColor);