#include <string>

int main();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
char* readFile(std::string filePath);
void compileShader(GLuint Shader, std::string filePath, std::string shaderType);
void updateColor(GLfloat* greenColor);
void bindTexture(GLenum textureNumber, GLenum textureType, const char* texturePath, GLuint textureObject);
void do_movement();
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);