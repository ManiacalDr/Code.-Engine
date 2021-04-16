//Made by Gregory Watts
#ifndef SPRITE_H
#define SPRITE_H
#include"object.hpp"
#include<string>

class Collision : public Object { // While this does also inherit from object, this information is necessary for the collision box
public:
	Collision(glm::vec3 p, double r, glm::vec3 s) {

	}
};

class Animator : public Object { // This class might do some magic to work
public:
	Animator(glm::vec3 p, double r, glm::vec3 s) {

	}
};

class Sprite : public Object
{
public:
	Sprite();
	~Sprite();
	Sprite(std::string n) { name = n; }
	Sprite(std::string n, glm::vec3 p, double r, glm::vec3 s) {

	}

private:
	std::string name;
};

#endif // !1