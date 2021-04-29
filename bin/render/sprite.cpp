// Standard Libraries
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>

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
#include <box2d/box2d.h>
#include "scene.h"

Sprite::Sprite() {

}

Sprite::~Sprite() {

}

Sprite::Sprite(std::string n, std::string t, glm::vec3 p, double r, glm::vec3 s, std::string i) : Object(p, r, s, i) {
	name = n;
	UV = defaultUV;



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

Sprite::Sprite(std::string n, glm::mat4x2 uv, std::string t, glm::vec3 p, double r, glm::vec3 s, std::string i) : Object(p, r, s, i) {
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

Sprite::Sprite(Scene* sc,bool dyn,std::string n, glm::mat4x2 uv, GLuint t, glm::vec3 p, double r, glm::vec3 s, std::string i) : Object(p, r, s, i) {
	name = n;
	UV = uv;
    scene = sc;
	texture = t;

}

void Sprite::addCollider(bool dyn)
{

	collider = collision.addRect(scene,this->position.x,this->position.y,this->scaleValue.x,this->scaleValue.y,dyn);
}

void Sprite::removeCollier() {

	collider = nullptr;
}

void Sprite::colliderTranslate()
{
	if (collider != nullptr)
	{
		this->position.x = collider->GetPosition().x * M2P;
		this->position.y = collider->GetPosition().y * M2P;
		this->rotation = collider->GetAngle() * (180.0 / 3.141592653589793238463);
	}
}

void Sprite::spriteTranslate()
{
	if (collider != nullptr)
	{
		collider->SetTransform(b2Vec2(this->position.x * P2M, this->position.y * P2M), this->rotation / (180.0 / 3.141592653589793238463));
	}
}