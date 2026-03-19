#include <iostream>
#include <raylib.h>
#include <cmath>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Vector2 operator-(const Vector2& a, const Vector2& b)
{
	return Vector2{
		a.x - b.x,
		a.y - b.y
	};
}

float edge_cross(const Vector2& a, const Vector2& b, const Vector2& p)
{
	Vector2 e1 = p - a;
	Vector2 e2 = b - a;

	float cross = (e2.x * e1.y) - (e2.y * e1.x); 
	return cross;
}

int main()
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window");

	Vector2 vertices[] = {
		{ WINDOW_WIDTH / 2 + 3, 23 },         
		{ WINDOW_WIDTH - 17, WINDOW_HEIGHT - 5 },
		{ 27, WINDOW_HEIGHT - 12 }              
	};

	float minX = std::min(std::min(vertices[0].x, vertices[1].x), vertices[2].x);
	float minY = std::min(std::min(vertices[0].y, vertices[1].y), vertices[2].y);
	float maxX = std::max(std::max(vertices[0].x, vertices[1].x), vertices[2].x);
	float maxY = std::max(std::max(vertices[0].y, vertices[1].y), vertices[2].y);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(GREEN);
		
		for (float i = minY; i <= maxY; ++i)
		{
			for (float j = minX; j <= maxX; ++j)
			{
				Vector2 P = { j, i };
				
				float w1 = edge_cross(vertices[0], vertices[1], P);
				float w2 = edge_cross(vertices[1], vertices[2], P);
				float w3 = edge_cross(vertices[2], vertices[0], P);

				bool in_triangle = w1 >= 0 && w2 >= 0 && w3 >= 0;

				if(in_triangle) DrawPixel(j, i, RED);
			}
		}

		EndDrawing();
	}

	CloseWindow();
}