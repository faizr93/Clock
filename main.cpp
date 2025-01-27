#include <raylib.h>
#include <vector>

struct Particle
{
    Rectangle rect; // The rectangle representing the particle
    float speed;    // The speed of the particle
    // Add other properties here, e.g., direction
};

int main()
{
    // Init Variables
    const int TARGET_FPS = 60;
    SetTargetFPS(TARGET_FPS);
    InitWindow(800, 600, "Hello Raylib!");

    std::vector<Particle> rain_particles;

    // Create Particles with Randomized Positions and Speeds
    for (int i = 0; i < 200; i++)
    {
        Particle particle;
        particle.rect.x = GetRandomValue(0, GetScreenWidth());
        particle.rect.y = GetRandomValue(0, GetScreenHeight());
        particle.rect.width = GetRandomValue(1, 3);
        particle.rect.height = particle.rect.width + GetRandomValue(2, 4);
        particle.speed = GetRandomValue(1, 5);
        rain_particles.push_back(particle);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Rain Simulation", 350, 280, 20, RAYWHITE);

        for (auto &particle : rain_particles)
        {
            DrawRectangle(
                particle.rect.x,
                particle.rect.y,
                particle.rect.width,
                particle.rect.height,
                BLUE);

            particle.rect.y += particle.speed;

            // Reset particle if it leaves the screen
            if (static_cast<int>(particle.rect.y) > GetScreenHeight())
            {
                particle.rect.width = GetRandomValue(1, 3);
                particle.rect.height = particle.rect.width + GetRandomValue(2, 4);
                particle.rect.x = GetRandomValue(0, GetScreenWidth());
                particle.rect.y = 0;
                particle.speed = GetRandomValue(1, 4);
            }

            // Increase speed if the particle passes halfway down the screen
            if (static_cast<int>(particle.rect.y) % 20 == 0 && particle.speed < 11)
            {
                particle.speed+= 0.1f;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
