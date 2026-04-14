#include "Beam.h"
#include "raymath.h"

Beam::Beam(Node* node1, Node* node2, float k, float d) {
    this->n1 = node1;
    this->n2 = node2;
    this->stiffness = k;
    this->damping = d;
    // Calculate the distance they started at as the 'natural' length
    this->restLength = Vector2Distance(n1->position, n2->position);
    this->isBroken = false;
    this->plasticDeflectionThreshold = 0.5f;
    this->breakLimit = 0.7f;
}
void Beam::Update(float dt, bool simulateDeflection)
{
    //will sum up calculations going along
    // 1 calculation
    if (isBroken) return;
    
    // 3 calculations
    Vector2 deltaPos = Vector2Subtract(n2->position, n1->position); 
    float currentLength = Vector2Length(deltaPos);
    // 4 calculations
    if (currentLength == 0) return;
    // 5 calculations
    float x = currentLength - this->restLength;
    // 6 calculations
    if (simulateDeflection)
    {
        // 7 calculations
        float deflection = fabsf(x) / restLength;
        // 8 calculations
        if (deflection > plasticDeflectionThreshold)
        {
            // 13 calculations
            float deflectionAmount = (x > 0 ? 1 : -1) * (deflection - plasticDeflectionThreshold) * restLength * 0.1f;
            // 14 calculations
            restLength += deflectionAmount;
        }
        // 15 calculations
        if (deflection > breakLimit)
        {
            isBroken = true;
            return;
        }
    }
    // 16 calculations
    float springForce = stiffness * x;
    // 18 calculations
    Vector2 relativeVelocity = Vector2Subtract(n2->velocity, n1->velocity);
    // 26 calculations
    Vector2 direction = Vector2Normalize(deltaPos);
    // 29 calculations
    float vRelative = Vector2DotProduct(relativeVelocity, direction);
    // 30 calculations
    float dampingForce = vRelative * damping;
    // 31 calculations
    float totalForce = springForce + dampingForce;
    // 33 calculations
    Vector2 forceVector = Vector2Scale(direction, totalForce);
    // 35 calculations
    n1->velocity.x += (forceVector.x / n1->mass) * dt;
    n1->velocity.y += (forceVector.y / n1->mass) * dt;
    // 37 calculations
    n2->velocity.x -= (forceVector.x / n2->mass) * dt;
    n2->velocity.y -= (forceVector.y / n2->mass) * dt;
}

void Beam::Draw()
{
    DrawLineEx(n1->position, n2->position, 2.0f, GREEN);
}