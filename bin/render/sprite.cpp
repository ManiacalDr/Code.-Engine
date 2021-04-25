// Standard Libraries
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "stb_image.h"

#define GLEW_STATIC
// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/ext.hpp>

#include <common/textureshader.hpp>

#include<GL/glu.h>

#include "sprite.h"

Sprite::Sprite() {

}

Sprite::~Sprite() {

}

Sprite::Sprite(std::string n, glm::mat2x4 uv, std::string t, glm::vec3 p, double r, glm::vec3 s, std::string i) : Object(p, r, s, i) {
	name = n;
	UV = uv;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	int width, height, nrChannels;

	unsigned char* data = stbi_load("assets/textures/failed.jpg", &width, &height, &nrChannels, 3);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	data = stbi_load(t.c_str(), &width, &height, &nrChannels, 3);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Sprite::Sprite(std::string n, glm::mat2x4 uv, GLuint t, glm::vec3 p, double r, glm::vec3 s, std::string i) : Object(p, r, s, i) {
	name = n;
	UV = uv;

	texture = t;
}