//Made by Gregory Watts
#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <string>
#include "object.hpp"
#include <box2d/box2d.h>

class Scene
{
public:
	Object* root;
	b2World* world;
	Object* playerSprite;//Sprite assigned to player
	std::vector<Object*> objects;
	std::vector<Object*> sprites;

	Scene();
	~Scene();

	void worldStep();

	void processFile(const std::string file);
	void writeFile(const std::string file);

private:

};

#endif