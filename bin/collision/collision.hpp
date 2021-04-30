#include "scene.h"
#include <iostream>
#include "scene.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <Box2D/Box2D.h>

#ifndef COLLISION_H
#define COLLISION_H

class Collision {
public:
	Scene* scene;

	Collision() {};
	~Collision() {};

	void setScene(Scene* scn) {
		scene = scn;
	}

	const int WIDTH = 640;
	const int HEIGHT = 480;
	const float M2P = 32;
	const float P2M = 1 / M2P;


	b2Body* addRect(Scene* scene, int x, int y, int w, int h, bool dyn = true)//Creates world where box colliders live
	{
		setScene(scene);
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