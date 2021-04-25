//Made by Gregory Watts
#ifndef SPRITE_H
#define SPRITE_H

#include"object.hpp"
#include<string>

class Sprite : public Object
{
public:
	std::string name;
	glm::mat2x4 UV; // if applicable
	GLuint texture;

	Sprite();
	~Sprite();
	Sprite(std::string n) { name = n; }
	Sprite(std::string n, glm::mat2x4 uv, std::string t, glm::vec3 p, double r, glm::vec3 s, std::string i);
	Sprite(std::string n, glm::mat2x4 uv, GLuint t, glm::vec3 p, double r, glm::vec3 s, std::string i);

private:

};

#endif