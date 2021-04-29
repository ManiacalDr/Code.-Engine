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
	std::string name;
	glm::mat2x4 UV; // if applicable
	GLuint texture;
	Collision collision;
	b2Body* collider;
	Scene* scene;

	const float M2P = 32;
	const float P2M = 1 / M2P;

	Sprite();
	~Sprite();
	Sprite(std::string n) { name = n; }
	Sprite(std::string n, glm::mat2x4 uv, std::string t, glm::vec3 p, double r, glm::vec3 s, std::string i);
	Sprite(Scene* scene,bool dyn,std::string n, glm::mat2x4 uv, GLuint t, glm::vec3 p, double r, glm::vec3 s, std::string i);
	void addCollider(bool);

	void colliderTranslate();
	void spriteTranslate();

private:

};

#endif