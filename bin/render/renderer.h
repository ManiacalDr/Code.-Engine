// Made by Gregory Watts
#ifndef RENDERER_H
#define RENDERER_H
// Standard Libraries
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <boost/filesystem.hpp>

#define GLEW_STATIC
// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/ext.hpp>

#include <common/textureshader.hpp>

#include<GL/glu.h>
#include "scene.h"
#include "editor.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#define reportError(s) _ReportError(__LINE__, (s))

enum class RenderMode {
	NONE,
	GAME,
	EDITOR,
	MENU
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
	void render(Scene*);
	void updateScene(Scene* scn) {
		scene = scn;
	}

	bool finish = true;

	RenderMode getMode() {
		return mode;
	}

	void setEditor(Editor* edi) {
		editor = edi;
	}

	void setScene(Scene* scn) {
		scene = scn;
	}

	void setCam(glm::vec3 c) {
		cam = c;
	}

	void playerMove(std::string);

private:
	GLuint VBO = 0, VAO = 0, textVAO = 0, textVBO = 0;
	GLuint ProgramID = 0, TextID = 0;
	glm::mat4 p = glm::mat4(1.0f);
	glm::mat4 v = glm::mat4(1.0f);
	GLuint MVP = 0;
	GLuint COLOR = 0;
	GLuint UV = 0;
	glm::vec3 cam = glm::vec3(0.0, 0.0, 0.0);
	glm::mat4 mvp = glm::mat4(1.0f);
	bool pressed[GLFW_KEY_MENU];

	GLFWwindow* window = 0;
	Editor* editor;
	Scene* scene;

	RenderMode mode = RenderMode::EDITOR;
	std::map<char, Character> Characters;

	void KeyboardCB(int key, int scancode, int action, int mods);

	void mouse_button_callback(int button, int action, int mods);

	void framebuffer_size_callback(int width, int height);

	void initialize();

	void RenderText(std::string, float, float, float, glm::vec3);

	float vertices[30] = {
		// positions         
		 0.0f,  0.0f, 0.0f,   0.0f, 1.0f,   // top right
		 1.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // bottom left
		1.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		0.0f,  1.0f, 0.0f,   0.0f, 0.0f,   // top left 
		0.0f,  0.0f, 0.0f,   0.0f, 1.0f,   // top right
	};

	static void KeyboardCB(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
		renderer->KeyboardCB(key, scancode, action, mods);
	}

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		//Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
		//renderer->framebuffer_size_callback(width, height);
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
		renderer->mouse_button_callback(button, action, mods);
	}

	void updateCam(glm::mat4 update);

};

#endif