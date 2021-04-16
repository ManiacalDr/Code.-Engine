#ifndef RENDERER_H
#define RENDERER_H
// Standard Libraries
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/ext.hpp>

#include <common/textureshader.hpp>

#include<GL/glu.h>
#include "scene.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#define reportError(s) _ReportError(__LINE__, (s))

enum class RenderMode {
	GAME,
	EDITOR
};

struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	void render(Scene&);
	bool finish = true;
	std::map<char, Character> Characters;

private:
	GLuint VBO, VAO, textVAO, textVBO;
	GLuint ProgramID, TextID;
	GLuint texture[16];
	GLuint MVP;
	glm::vec3 cam = glm::vec3(0.0,0.0,0.0);
	glm::mat4 mvp;

	GLFWwindow* window;

	float speed = 0.5;
	int numTextures = 1;
	RenderMode mode = Renderer::GAME;

	void initialize();

	void updateCam(glm::mat4 update);
	void RenderText(std::string, float, float, float, glm::vec3);

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

#endif