//Made by Gregory Watts
#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <memory>
#include <string>
#include "object.hpp"
#include <box2d/box2d.h>

///Unused contact listener, in future this would control when two objects connect what to do.
class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) {

		b2BodyUserData a = contact->GetFixtureA()->GetBody()->GetUserData();
	
		b2BodyUserData b = contact->GetFixtureB()->GetBody()->GetUserData();

		std::cout << a.pointer << " " << b.pointer;

	}
};

// Scene class, stores everything neccessary for the scene, including seperted clickable objects, sprites, ans where the player starts in a scene.
// Also is responsible for the Collision model
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
	~Scene() {};

	void worldStep();

	void saveSprites(const std::string file);

	void readSprites(const std::string file);

};

#endif