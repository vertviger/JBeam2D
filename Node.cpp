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
    // 1. Define Gravity (e.g., 981 pixels/s^2)
    Vector2 gravity = { 0, 981.0f };

    // 2. Acceleration = Force / Mass (Newton's 2nd Law)
    // For now, let's just use gravity as our acceleration
    Vector2 acceleration = gravity;

    // 3. Velocity = Velocity + (Acceleration * Time)
    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;

    // 4. Position = Position + (Velocity * Time)
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // 5. Simple Floor Collision (so it doesn't fall forever)
    if (position.y > screenSize.y) {
        position.y = screenSize.y;
        velocity.y *= -0.7f; // Bounce with 50% energy loss
    }

    if (position.x > screenSize.x) {
        position.x = screenSize.x;
        velocity.x *= -0.7f; // Bounce with 50% energy loss
    }

    if (position.y < 0) {
        position.y = 0;
        velocity.y *= -0.7f; // Bounce with 50% energy loss
    }

    if (position.x < 0) {
        position.x = 0;
        velocity.x *= -0.7f; // Bounce with 50% energy loss
    }
}

void Node::Draw()
{
	DrawCircleV(this->position, radius, color);
}
