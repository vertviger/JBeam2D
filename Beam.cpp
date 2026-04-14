#include "Beam.h"
#include "raymath.h"

Beam::Beam(Node* node1, Node* node2, float k, float d) {
    this->n1 = node1;
    this->n2 = node2;
    this->stiffness = k;
    this->damping = d;
    // Calculate the distance they started at as the 'natural' length
    this->restLength = Vector2Distance(n1->position, n2->position);
}
void Beam::Update(float dt)
{
    Vector2 deltaPos = Vector2Subtract(n2->position, n1->position);
    float currentLength = Vector2Length(deltaPos);

    if (currentLength == 0) return;

    float x = currentLength - this->restLength;
    float springForce = stiffness * x;

    Vector2 relativeVelocity = Vector2Subtract(n2->velocity, n1->velocity);
    Vector2 direction = Vector2Normalize(deltaPos);
    float vRelative = Vector2DotProduct(relativeVelocity, direction);
    float dampingForce = vRelative * damping;

    float totalForce = springForce + dampingForce;
    Vector2 forceVector = Vector2Scale(direction, totalForce);

    n1->velocity.x = (forceVector.x / n1->mass) * dt;
    n1->velocity.y = (forceVector.y / n1->mass) * dt;
    
    n2->velocity.x = (forceVector.x / n2->mass) * dt;
    n2->velocity.y = (forceVector.y / n2->mass) * dt;
}

void Beam::Draw()
{
    DrawLineEx(n1->position, n2->position, 2.0f, GREEN);
}