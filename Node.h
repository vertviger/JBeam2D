#ifndef NODE_H
#define NODE_H
#include "raylib.h"

struct Node
{
	Vector2 position;
	Vector2 velocity;
	float radius;
	float mass;
	bool isBeingDragged;
	Color color;

	Node(Vector2 pos, float mass, float radius);

	void Update(float dt, Vector2 screenSize);

	void Draw();

};

#endif
