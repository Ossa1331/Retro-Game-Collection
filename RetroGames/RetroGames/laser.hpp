#pragma once

#include<raylib.h>

class Laser {
public:
	Laser(Vector2 position, int speed);
	void UpdateLaser();
	void DrawLaser();
	bool active;

	Rectangle GetRect();
private:
	Vector2 position;
	int speed;
};