//Made by Michael Alcala
#ifndef COLLISION_H
#define COLLISION_H

#include "scene.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Box2D/Box2D.h>

/// Collision class to store values necessary for creating colliders inside of the collision model.
class Collision {
public:
	Collision() {};
	~Collision() {};

	const int WIDTH = 640;
	const int HEIGHT = 480;
	const float M2P = 32;
	const float P2M = 1 / M2P;

	/// This function sets up the physics body inside of the curretnly loaded scene.
	b2Body* addRect(Scene* scene, int x, int y, int w, int h, bool dyn = true)//Creates world where box colliders live
	{
		b2BodyDef bodydef;
		bodydef.position.Set(x * P2M, y * P2M);
		if (dyn)
			bodydef.type = b2_dynamicBody;
		b2Body* body = scene->world->CreateBody(&bodydef);

		b2PolygonShape shape;
		shape.SetAsBox(P2M * w / 2, P2M * h / 2);

		b2FixtureDef fixturedef;
		fixturedef.shape = &shape;
		fixturedef.density = 1.0;
		body->CreateFixture(&fixturedef);

		return body;
	}
};

#endif