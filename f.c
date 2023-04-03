#include <math.h>
#include <stdio.h>

#define MAP_WIDTH 8
#define MAP_HEIGHT 7
#define MAX_DISTANCE 10.0f
#define STEP_SIZE 0.01f

typedef struct {
	float x, y;
} Vector2;

int map[MAP_WIDTH][MAP_HEIGHT] = {
		{1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1},
};

int getMapValue(int x, int y) {
	if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) {
		return 1;  // Assume walls surround the map to prevent going out of bounds
	}
	return map[x][y];
}

Vector2 getRayDirection(Vector2 observerPosition, Vector2 pointOfView, float angle) {
	Vector2 rayDirection;
	rayDirection.x = pointOfView.x - observerPosition.x;
	rayDirection.y = pointOfView.y - observerPosition.y;
	float length = sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y);
	rayDirection.x /= length;
	rayDirection.y /= length;

	float sinAngle = sin(angle);
	float cosAngle = cos(angle);

	// Rotate the ray direction vector by the specified angle
	Vector2 rayDirectionRotated = {
			cosAngle * rayDirection.x + sinAngle * rayDirection.y,
			-sinAngle * rayDirection.x + cosAngle * rayDirection.y
	};
	return rayDirectionRotated;
}

float rayMarch(Vector2 position, Vector2 direction) {
	float distance = 0;
	while (distance < MAX_DISTANCE) {
		int mapX = (int)position.x;
		int mapY = (int)position.y;
		if (getMapValue(mapX, mapY) == 1) {
			return distance;  // Hit a wall
		}
		distance += STEP_SIZE;
		position.x += direction.x * STEP_SIZE;
		position.y += direction.y * STEP_SIZE;
	}
	return MAX_DISTANCE;  // Didn't hit anything within the maximum distance
}

int main() {
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
			printf("%d", getMapValue(i, j));
		printf("\n");
	}
	Vector2 observerPosition = {1.5f, 1.5f};
	Vector2 pointOfView = {1.0f, 8.0f};

	for (float angle = 0.0f; angle < 2 * M_PI; angle += 0.1f) {
		Vector2 direction = getRayDirection(observerPosition, pointOfView, angle);
		float distance = rayMarch(observerPosition, direction);
		printf("Angle: %f, Distance: %f\n", angle, distance);
	}
	return 0;
}
