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

void drawTriangle(Vector2 v0, Vector2 v1, Vector2 v2, Color c0, Color c1, Color c2)
{
    float minX = std::min({ v0.x, v1.x, v2.x });
    float maxX = std::max({ v0.x, v1.x, v2.x });

    float minY = std::min({ v0.y, v1.y, v2.y });
    float maxY = std::max({ v0.y, v1.y, v2.y });

    float area = edge(v0, v1, v2);

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
                float alpha = w0 / area;
                float beta = w1 / area;
                float gamma = w2 / area;

                int r = (int)(alpha * c0.r + beta * c1.r + gamma * c2.r);
                int g = (int)(alpha * c0.g + beta * c1.g + gamma * c2.g);
                int b = (int)(alpha * c0.b + beta * c1.b + gamma * c2.b);
                
                Color color = { r, g, b, 255 };

                DrawPixel(x, y, color);
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

    Color tri1Colors[] = {
        {255, 0, 0, 255},
        {0, 255, 0, 255},
        {0, 0, 255, 255}
    };

    Color tri2Colors[] = {
        {123, 55, 24, 255},
        {25, 87, 122, 255},
        {0, 0, 255, 0}
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        drawTriangle(tri1[0], tri1[1], tri1[2], tri1Colors[0], tri1Colors[1], tri1Colors[2]);
        drawTriangle(tri2[0], tri2[1], tri2[2], tri2Colors[0], tri2Colors[1], tri2Colors[2]);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}