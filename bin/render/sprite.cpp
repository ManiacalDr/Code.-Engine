// Standard Libraries
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>
#include<MMsystem.h>
#include "audio.h"

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
#include <time.h>

Playaudio currentlyplaying;

Sprite::Sprite() {

}

Sprite::~Sprite() {

}

Sprite::Sprite(std::string n, std::string t, glm::vec3 p, double r, glm::vec3 s, std::string i) : Object(p, r, s, i) {
	name = n;

	curFrame = defaultUV;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	int width, height, nrChannels;

	//unsigned char* data = stbi_load("assets/textures/entities/failed.jpg", &width, &height, &nrChannels, 4);

	//if (data)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}

	unsigned char* data = stbi_load(t.c_str(), &width, &height, &nrChannels, 4);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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

	curFrame = defaultUV;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	int width, height, nrChannels;

	//unsigned char* data = stbi_load("assets/textures/entities/failed.jpg", &width, &height, &nrChannels, 3);

	//if (data)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}

	unsigned char* data = stbi_load(t.c_str(), &width, &height, &nrChannels, 4);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Sprite::Sprite(bool dyn,std::string n, glm::mat4x2 uv, GLuint t, glm::vec3 p, double r, glm::vec3 s, std::string i) : Object(p, r, s, i) {
	name = n;
	texture = t;
	curFrame = defaultUV;

}

void Sprite::addCollider(bool dyn, Scene* scene)
{

	collider = collision.addRect(scene, this->position.x,this->position.y,this->scaleValue.x,this->scaleValue.y, dyn);
}

void Sprite::setUV(glm::vec2 start, glm::vec2 end, int frames, glm::vec2 frameSize) {
	UV = new glm::mat4x2[frames];
	glm::vec2 first = start;
	for (int i = 0; i < frames; i++)
	{
		if (first.x >= end.x)//if row is done, go to the next one
		{
			first.x = start.x;
			first.y += frameSize.y;
		}
		if (first.y >= end.y)//if the whole page is done before i=frames, then it breaks;
		{
			break;
		}
		glm::mat4x2 frameSet(first.x/end.x, first.y/end.y, 
			first.x/end.x, (first.y + frameSize.y)/end.y, 
			(first.x + frameSize.x)/end.x, (first.y)/end.y,
			(first.x + frameSize.x) / end.x, (first.y + frameSize.y) / end.y);
		UV[i] = frameSet;//marks one frame
		first.x += frameSize.x;
	}
	curFrame = UV[0];
}

void Sprite::setCurFrame(int frame)
{
	curFrame = UV[frame];
}

void Sprite::setAnimation(std::string animationName,int frames[], int frameSize)//adds all the frames from the number in frames[i]
{
	animationList[animationName] = new glm::mat4x2[frameSize];
	for (int i = 0; i < frameSize; i++)
	{
		animationList[animationName][i] = UV[frames[i]];
	}
}

void Sprite::startAnimation(std::string animationName, int size)
{
	if (UV != nullptr)
	{
		if (fpsCount % (int)fps == 0)
		{
			if (frame >= size)
				frame = 0;
			curFrame = animationList[animationName][frame];
			frame++;
			fpsCount = 1;
		}
		fpsCount++;
	}
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

void Sprite::makePlayer(Scene* scene)
{
	data.isPlayer = true;
	scene->playerSprite = this;
}

void Sprite::makeEnemy(Scene* scene)
{
	data.isEnemy = true;
}

void Sprite::playerControl(std::string key)
{
	if (key == "W")
	{
		if (this->collider == nullptr)
		{
			this->position = glm::vec3(position.x, position.y + 5, position.z);
			startAnimation("upWalk", 3);
			currentlyplaying.DragonRoar();
		}
		else
		{
			this->collider->ApplyLinearImpulseToCenter(b2Vec2(0, 50), true);
			currentlyplaying.DragonRoar();
		}
	}
	else if (key == "A")
	{
		this->position = glm::vec3(position.x-5, position.y, position.z);
		startAnimation("leftWalk", 3);
		currentlyplaying.DragonRoar();
	}
	else if (key == "S")
	{
		if (this->collider == nullptr)
		{
			this->position = glm::vec3(position.x, position.y - 5, position.z);
			startAnimation("downWalk", 3);
			currentlyplaying.DragonRoar();
		}

	}
	else if (key == "D")
	{
		this->position = glm::vec3(position.x+5, position.y, position.z);
		startAnimation("rightWalk", 3);
		currentlyplaying.DragonRoar();
	}

	
	spriteTranslate();
}