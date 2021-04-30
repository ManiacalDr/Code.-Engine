//Made by Gregory Watts
#ifndef SPRITE_H
#define SPRITE_H

#include"object.hpp"
#include<string>
#include "scene.h"
#include<box2d/box2d.h>
#include "../collision/collision.hpp"
#include <map>

class Sprite : public Object
{
public:
	const glm::mat4x2 defaultUV = glm::mat4x2(0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0);
	std::string name;
	glm::vec4 color = glm::vec4(1.0);
	glm::mat4x2* UV; //UV is the list of all frames once set up
	glm::mat4x2 curFrame;//Is either the defaultUV or the current frame of UV
	std::map<std::string, glm::mat4x2* > animationList;//Stores animation names and frames together
	bool animating = false;
	int frame = 0;
	GLuint texture;
	Collision collision;
	b2Body* collider;
	Scene* scene;

	const float M2P = 32;
	const float P2M = 1 / M2P;
	const float fps = 5;
	int fpsCount = 0;

	Sprite();
	~Sprite();
	Sprite(std::string n) { name = n; }
	Sprite(std::string n, std::string t, glm::vec3 p, double r, glm::vec3 s, std::string i);
	Sprite(std::string n, glm::mat4x2 uv, std::string t, glm::vec3 p, double r, glm::vec3 s, std::string i);
	Sprite(Scene* scene,bool dyn,std::string n, glm::mat4x2 uv, GLuint t, glm::vec3 p, double r, glm::vec3 s, std::string i);

	void addCollider(bool);

	void setUV(glm::vec2 start, glm::vec2 end, int frames, glm::vec2 frameSize);//Sets up UV map
	void setAnimation(std::string, int frames[], int frameSize);//Sets up animation
	void setCurFrame(int frame);//sets frame that renders
	void startAnimation(std::string,int);//starts animation

	void colliderTranslate();//translates sprite to collider
	void spriteTranslate();//translates collider to sprite

	void makePlayer();//makes sprite the player
	void playerControl(std::string);//Move player

private:

};

#endif