#include <iostream>
#include <raylib.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

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

void rotateVector(Vector2& vec, float angle, const Vector2& center)
{
    vec.x -= center.x;
    vec.y -= center.y;

    float x = vec.x;
    float y = vec.y;

    vec.x = x * cos(angle) - y * sin(angle);
    vec.y = x * sin(angle) + y * cos(angle);

    vec.x += center.x;
    vec.y += center.y;
}

void drawTriangle(Vector2 v0, Vector2 v1, Vector2 v2, Color c0, Color c1, Color c2)
{
    int minX = (int)std::floor(std::min({ v0.x, v1.x, v2.x }));
    int minY = (int)std::floor(std::min({ v0.y, v1.y, v2.y }));

    int maxX = (int)std::ceil(std::max({ v0.x, v1.x, v2.x }));
    int maxY = (int)std::ceil(std::max({ v0.y, v1.y, v2.y }));

    float area = edge(v0, v1, v2);

    float deltaW0Col = v1.y - v2.y;
    float deltaW1Col = v2.y - v0.y;
    float deltaW2Col = v0.y - v1.y;

    float deltaW0Row = v2.x - v1.x;
    float deltaW1Row = v0.x - v2.x;
    float deltaW2Row = v1.x - v0.x;

    Vector2 p = { minX, minY };

    float w0_row = edge(v1, v2, p);
    float w1_row = edge(v2, v0, p);
    float w2_row = edge(v0, v1, p);

    for (int y = minY; y <= maxY; y++)
    {
        float w0 = w0_row;
        float w1 = w1_row;
        float w2 = w2_row;

        for (int x = minX; x <= maxX; x++)
        {
            Vector2 p = { (float)x + 0.5f, (float)y + 0.5f };

            bool inside = true;

            if (w0 < 0.f || (w0 == 0.f && !top_left_edge(v1, v2))) inside = false;
            if (w1 < 0.f || (w1 == 0.f && !top_left_edge(v2, v0))) inside = false;
            if (w2 < 0.f || (w2 == 0.f && !top_left_edge(v0, v1))) inside = false;

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

            w0 += deltaW0Col;
            w1 += deltaW1Col;
            w2 += deltaW2Col;
        }

        w0_row += deltaW0Row;
        w1_row += deltaW1Row;
        w2_row += deltaW2Row;
    }
}

Vector2 getCenter(Vector2 triangle[3])
{
    float centerX = (triangle[0].x + triangle[1].x + triangle[2].x) / 3.f;
    float centerY = (triangle[0].y + triangle[1].y + triangle[2].y) / 3.f;
    return { centerX, centerY };
}

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Full Subpixel Rasterizer");
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
        {0, 0, 255, 255}
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        float angle = 1.0f * 0.01745329251f;

        std::stringstream ss;
        ss << "FPS: " << std::fixed << std::setprecision(0) << (1.f / GetFrameTime());
        std::string fps = ss.str();

        DrawText(fps.c_str(), 48, 48, 24, WHITE);

        Vector2 center = getCenter(tri1);

        rotateVector(tri1[0], angle, center);
        rotateVector(tri1[1], angle, center);
        rotateVector(tri1[2], angle, center);

        drawTriangle(tri1[0], tri1[1], tri1[2], tri1Colors[0], tri1Colors[1], tri1Colors[2]);
        drawTriangle(tri2[0], tri2[1], tri2[2], tri2Colors[0], tri2Colors[1], tri2Colors[2]);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}