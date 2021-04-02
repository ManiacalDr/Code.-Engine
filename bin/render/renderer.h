// Standard Libraries
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/ext.hpp>

#include <common/textureshader.hpp>

#include<GL/glu.h>
using namespace glm;
#define reportError(s) _ReportError(__LINE__, (s))

class Renderer
{
public:
	Renderer();
	~Renderer();
	void render();
	bool finish = true;

private:
	GLuint VBO, VAO;
	GLuint programID;
	GLuint texture;

	GLFWwindow* window;

	void initialize();

	float vertices[30] = {
		// positions         // texture coords
		 0.0f,  0.0f, 0.0f,   0.0f, 1.0f,   // top right
		 1.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // bottom left
		1.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		0.0f,  1.0f, 0.0f,   0.0f, 0.0f,   // top left 
		0.0f,  0.0f, 0.0f,   0.0f, 1.0f,   // top right
	};
};