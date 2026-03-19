#include <iostream>
#include <raylib.h>
#include <cmath>
#include <algorithm>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Vector2 operator-(const Vector2& a, const Vector2& b)
{
    return { a.x - b.x, a.y - b.y };
}

float edge(const Vector2& a, const Vector2& b, const Vector2& p)
{
    Vector2 e1 = p - a;
    Vector2 e2 = b - a;
    return (e2.x * e1.y) - (e2.y * e1.x);
}

bool top_left_edge(const Vector2& a, const Vector2& b)
{
    Vector2 e = b - a;

    bool is_top = (e.y == 0 && e.x > 0);
    bool is_left = (e.y < 0);

    return is_top || is_left;
}

void drawTriangle(Vector2 v0, Vector2 v1, Vector2 v2, Color col)
{
    float minX = std::min({ v0.x, v1.x, v2.x });
    float maxX = std::max({ v0.x, v1.x, v2.x });

    float minY = std::min({ v0.y, v1.y, v2.y });
    float maxY = std::max({ v0.y, v1.y, v2.y });

    for (float y = minY; y <= maxY; y++)
    {
        for (float x = minX; x <= maxX; x++)
        {
            Vector2 p = { (float)x + 0.5f, (float)y + 0.5f };

            float w0 = edge(v1, v2, p);
            float w1 = edge(v2, v0, p);
            float w2 = edge(v0, v1, p);

            bool inside = true;

            if (w0 < 0 || (w0 == 0 && !top_left_edge(v1, v2))) inside = false;
            if (w1 < 0 || (w1 == 0 && !top_left_edge(v2, v0))) inside = false;
            if (w2 < 0 || (w2 == 0 && !top_left_edge(v0, v1))) inside = false;

            if (inside)
            {
                DrawPixel(x, y, col);
            }
        }
    }
}

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Fill Convention Test");
    SetTargetFPS(60);

    Vector2 tri1[] = {
        { 200, 120 },
        { 350, 500 },
        { 80, 480 }
    };

    Vector2 tri2[] = {
        { 360, 140 },
        { 550, 520 },
        { 250, 500 }
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        drawTriangle(tri1[0], tri1[1], tri1[2], RED);
        drawTriangle(tri2[0], tri2[1], tri2[2], GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}