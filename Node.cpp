#include "Node.h"
#include "raylib.h"

Node::Node(Vector2 pos, float mass, float radius)
{
	this->position = pos;
	this->mass = mass;
    this->radius = radius;
    this->velocity = { 0, 0 };
    this->isBeingDragged = false;
    this->color = ORANGE;
}
void Node::Update(float dt, Vector2 screenSize)
{
    Vector2 gravity = { 0, 0 };

    Vector2 acceleration = gravity;

    // 4 calculations
    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;
    // 5 calculations
    float damping = this->mass / 10000;
    // 9 calculations
    velocity.x -= velocity.x * damping;
    velocity.y -= velocity.y * damping;

    // 13 calculations
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // Floor Collision (so it doesn't fall forever)
    if (position.y > screenSize.y) 
    {
        position.y = screenSize.y;
        velocity.y *= -0.7f; 
    }

    if (position.x > screenSize.x) 
    {
        position.x = screenSize.x;
        velocity.x *= -0.7f; 
    }

    if (position.y < 0) 
    {
        position.y = 0;
        velocity.y *= -0.7f; 
    }

    if (position.x < 0) 
    {
        position.x = 0;
        velocity.x *= -0.7f;
    }
}

void Node::Draw()
{
	DrawCircleV(this->position, radius, color);
}
