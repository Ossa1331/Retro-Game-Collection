#include <raylib.h>
#include "spaceship.hpp"

Spaceship::Spaceship() {
	image = LoadTexture("Images/spaceship.png");

	position.x = (GetScreenWidth()-image.width)/2;
	position.y = GetScreenHeight()-image.height-100;
	lastFiredTime = 0.0;
	laserSound = LoadSound("Sounds/laser.ogg");
}
Spaceship:: ~Spaceship() {
	UnloadTexture(image);
	UnloadSound(laserSound);
}
void Spaceship::DrawSpaceship() {
	DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft() {
	position.x -= 3;
	if (position.x < 25) {
		position.x = 0;
	}
}
void Spaceship::MoveRight() {
	position.x += 3;
	if (position.x > GetScreenWidth() - image.width-25) {
		position.x = GetScreenWidth() - image.width;
	}
}

void Spaceship::FireLaser() {
	if (GetTime() - lastFiredTime >= 0.35) {
		lasers.push_back(Laser({ position.x + image.width / 2 - 2,position.y }, -3));
		lastFiredTime = GetTime();
		PlaySound(laserSound);
	}
	
}

Rectangle Spaceship::getRect()
{
	return { position.x,position.y, float(image.width), float(image.height) };
}

void Spaceship::Reset()
{
	position.x = (GetScreenWidth() - image.width) / 2.0f;
	position.y = GetScreenHeight() - image.height-100;
	lasers.clear();
}
