//Made by Gregory Watts
#ifndef SPRITE_H
#define SPRITE_H

#include"object.hpp"
#include<string>
#include "scene.h"
#include<box2d/box2d.h>
#include "../collision/collision.hpp"

class Sprite : public Object
{
public:
	const glm::mat4x2 defaultUV = glm::mat4x2(0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0);
	std::string name;
	glm::mat4x2* UV = new  glm::mat4x2(defaultUV);
	glm::mat4x2 curFrame;
	glm::mat4x2** animationList;
	glm::vec4 color = glm::vec4(1.0);
	bool animating = false;
	int animationSize = 0;
	int frame = 0;
	GLuint texture;
	Collision collision;
	b2Body* collider;
	Scene* scene;
	bool animation = false;

	const float M2P = 32;
	const float P2M = 1 / M2P;
	const float fps = 60;
	int fpsCount = 0;

	Sprite();
	~Sprite();
	Sprite(std::string n) { name = n; }
	Sprite(std::string n, std::string t, glm::vec3 p, double r, glm::vec3 s, std::string i);
	Sprite(std::string n, glm::mat4x2 uv, std::string t, glm::vec3 p, double r, glm::vec3 s, std::string i);
	Sprite(Scene* scene,bool dyn,std::string n, glm::mat4x2 uv, GLuint t, glm::vec3 p, double r, glm::vec3 s, std::string i);

	void addCollider(bool);
	void removeCollier();

	void setUV(glm::vec2 start, glm::vec2 end, int frames, glm::vec2 frameSize);
	void setAnimation(int frames[], int frameSize);
	void setCurFrame(int frame);
	void startAnimation(int,int);

	void colliderTranslate();
	void spriteTranslate();

private:

};

#endif