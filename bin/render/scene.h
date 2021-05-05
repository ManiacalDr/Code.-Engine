//Made by Gregory Watts
#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <memory>
#include <string>
#include "object.hpp"
#include <box2d/box2d.h>


class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) {

		//check if fixture A was a ball
		b2BodyUserData a = contact->GetFixtureA()->GetBody()->GetUserData();
		//if (auser.pointer)
			//spriteData* a = (auser.pointer;

		//check if fixture B was a ball
		b2BodyUserData b = contact->GetFixtureB()->GetBody()->GetUserData();
		//if (bodyUserData)
			//static_cast<Ball*>(bodyUserData)->startContact();
		std::cout << a.pointer << " " << b.pointer;

	}
};

class Scene
{
public:
	MyContactListener* contactListener;
	b2World* world;
	Object* playerSprite;//Sprite assigned to player
	std::vector<Object*> objects;
	std::vector<Object*> sprites;

	glm::vec3 playerStart = glm::vec3(0.0f);

	Scene();
	~Scene();

	void worldStep();

	void processFile(const std::string file);
	void writeFile(const std::string file);

	void saveSprites(const std::string file);

	void readSprites(const std::string file);

};

#endif