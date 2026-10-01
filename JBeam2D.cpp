#include "raylib.h"
#include "Node.h"
#include "Beam.h"
#include <vector>
#include <string>
#include <chrono>

std::string FormatWithDots(long value)
{
    std::string numWithDots = std::to_string(value);
    int insertPosition = numWithDots.length() - 3;

    while (insertPosition > 0)
    {
        numWithDots.insert(insertPosition, ".");
        insertPosition -= 3;
    }

    return numWithDots;
}

int main() 
{
    
    
    int screenWidth = 1280;
    int screenHeight = 720;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "BeamNG JBeam2D Simulation");
    Font monoFont = LoadFontEx("resources/fonts/jetbrains_mono.ttf", 80, 0, 250);
    // Simulation settings
    float physicsTimeStep = 0.0005f; // 0.5ms (2000Hz)
    float accumulator = 0.0f;
    long totalCalculations = 0;
    //Nodes
    float radius = 25;
    float mass = 10;
    bool showNodeLabel = false;
    //Beams
    float stiffness = 1000.0f;
    float damping = 10.0f;
    bool simulateDeflection = false;

    Node first = Node({ (float)screenWidth / 2, (float)screenHeight / 2 }, mass, radius);

    std::vector<Node> nodes;
    nodes.push_back(first);
    nodes.push_back(Node({ 500.0f, 300.0f }, mass, radius));
    nodes.push_back(Node({ 700.0f, 300.0f }, mass, radius));
    nodes.push_back(Node({ 500.0f, 500.0f }, mass, radius));
    nodes.push_back(Node({ 700.0f, 500.0f }, mass, radius));

    std::vector<Beam> beams;
    beams.push_back(Beam(&nodes[1], &nodes[2], stiffness, damping));
    beams.push_back(Beam(&nodes[2], &nodes[4], stiffness, damping));
    beams.push_back(Beam(&nodes[4], &nodes[3], stiffness, damping));
    beams.push_back(Beam(&nodes[3], &nodes[1], stiffness, damping));

    beams.push_back(Beam(&nodes[1], &nodes[4], stiffness, damping));
    beams.push_back(Beam(&nodes[2], &nodes[3], stiffness, damping));

    auto start = std::chrono::high_resolution_clock::now();

    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        //mouse interactions
        Vector2 mousePos = GetMousePosition();

        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        if (IsKeyPressed(KEY_B))
        {
            showNodeLabel = !showNodeLabel;
        }

        if (IsKeyPressed(KEY_D))
        {
            simulateDeflection = !simulateDeflection;
        }
        
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
                n.velocity.x = mousePos.x - n.position.x;
                n.velocity.y = mousePos.y - n.position.y;
                //first.position = mousePos;
            }
        }
        
        float deltaTime = GetFrameTime();
        accumulator += deltaTime;
        
        // physics
        while (accumulator >= physicsTimeStep) 
        {
            for (auto& b : beams)
            {
                b.Update(physicsTimeStep, simulateDeflection);
            }
            for (auto& n : nodes) 
            {
                n.Update(physicsTimeStep, { (float)screenWidth, (float)screenHeight });
            }
            totalCalculations += beams.size()*37; // got 37 calculations there, check out Beam.cpp
            totalCalculations += nodes.size() * 13; // got 13 calculations from the Node.cpp
            accumulator -= physicsTimeStep;
        }

        // graphics
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(TextFormat("Calculations: %s", FormatWithDots(totalCalculations).c_str()), 20, 20, 80, DARKGRAY);
        std::chrono::duration<float> elapsed = std::chrono::high_resolution_clock::now() - start;
        DrawText(TextFormat("Time: %.2fs", elapsed.count()),screenWidth*0.82, 0.95*screenHeight, 40, DARKGRAY);

        for (auto& b : beams)
        {
            b.Draw();
        }
        
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes[i].Draw();
            if (showNodeLabel)
            {
                int textX = (int)nodes[i].position.x+nodes[i].radius;
                int textY = (int)nodes[i].position.y-nodes[i].radius;
                DrawText(TextFormat("Node: %d", i), textX, textY, 12, MAGENTA);
            }
        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}