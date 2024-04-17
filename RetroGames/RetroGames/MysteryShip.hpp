#pragma once
#include <raylib.h>

class MysteryShip {
public:
	MysteryShip();
	~MysteryShip();

	void UpdateMysteryShip();
	void DrawMysteryShip();
	void SpawnMysteryShip();

	Rectangle GetRect();

	bool alive;
private:

	Vector2 position;
	Texture2D image;
	int speed;
};