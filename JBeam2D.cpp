#include "raylib.h"
#include "Node.h"
#include "Beam.h"
#include <vector>

int main() {
    const int screenWidth = 960;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "BeamNG Physics Lab");

    // Simulation settings
    float physicsTimeStep = 0.0005f; // 0.5ms (2000Hz)
    float accumulator = 0.0f;
    long totalCalculations = 0;
    //Nodes
    float radius = 20;
    

    Node first = Node({ screenWidth / 2, screenHeight / 2 }, 10, radius);

    std::vector<Node> nodes;
    nodes.push_back(first);
    nodes.push_back(Node({ 500.0f, 300.0f }, 10.0f, radius));
    nodes.push_back(Node({ 700.0f, 300.0f }, 10.0f, radius));
    nodes.push_back(Node({ 500.0f, 500.0f }, 10.0f, radius));
    nodes.push_back(Node({ 700.0f, 500.0f }, 10.0f, radius));

    std::vector<Beam> beams;
    //TODO: add Beams between all possible nodes. 
    
    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        //mouse interactions
        Vector2 mousePos = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto& n : nodes)
            {
                if (CheckCollisionPointCircle(mousePos, n.position, radius))
                {
                    n.isBeingDragged = true;
                    n.color = { 0, 255, 50, 125 };
                }
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            for (auto& n : nodes)
            {
                n.isBeingDragged = false;
                n.color = ORANGE;
            }
        }

        for (auto& n : nodes)
        {
            if (n.isBeingDragged)
            {
                n.velocity.x = mousePos.x - first.position.x;
                n.velocity.y = mousePos.y - first.position.y;
                //first.position = mousePos;
            }
        }
        
        float deltaTime = GetFrameTime();
        accumulator += deltaTime;

        // The "BeamNG" Heartbeat: Run the physics at 2000Hz 
        // regardless of the frame rate.
        while (accumulator >= physicsTimeStep) {

            // --- YOUR PHYSICS MATH GOES HERE ---
            // 1. Calculate Distances
            // 2. Solve Forces
            // 3. Update Positions
            for (auto& n : nodes) 
            {
                n.Update(physicsTimeStep, { screenWidth, screenHeight });
            }
            totalCalculations += 20; // Example: 20 ops per beam
            //TODO: update Beams positions 
            accumulator -= physicsTimeStep;
        }

        // --- DRAWING ---
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(TextFormat("Calculations: %ld", totalCalculations), 20, 20, 20, DARKGRAY);
        
        for (auto& n : nodes)
        {
            n.Draw();
        }
        //TODO: draw Beams
        EndDrawing();
    }

    CloseWindow();
    return 0;
}