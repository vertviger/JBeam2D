#ifndef BEAM_H
#define BEAM_H
#include "raylib.h"
#include "Node.h"

struct Beam {
    Node* n1; // Use pointers (Node*) to refer to the original nodes
    Node* n2;
    float restLength;
    float stiffness;
    float damping;

    bool isBroken;
    float plasticDeflectionThreshold;
    float breakLimit;

    Beam(Node* node1, Node* node2, float k, float d);
    void Update(float dt, bool simulateDeflection);
    void Draw();
};

#endif
