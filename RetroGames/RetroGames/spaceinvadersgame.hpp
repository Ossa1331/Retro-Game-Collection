#pragma once
#include <spaceship.hpp>
#include <obstacle.hpp>
#include <Alien.hpp>
#include <MysteryShip.hpp>

class SpaceInvadersGame {
public:
	SpaceInvadersGame();
	~SpaceInvadersGame();

	void DrawSpaceInvaders();
	void UpdateSpaceInvaders();
	void HandleInputSpaceInvaders();

	bool run;
	int lives;
	int score;

	int highscore;

	Music music;

private:
	void DeleteInactiveLasers();
	std::vector<Laser> alienLasers;

	Spaceship spaceship;

	std::vector<Obstacle>obstacles;
	std::vector<Obstacle> CreateObstacles();

	std::vector<Alien> aliens;

	std::vector<Alien> CreateAliens();

	void MoveAliens();
	void MoveDownAliens(int distance);
	int aliensDirection;
	
	
	void AlienShootLaser();
	constexpr static float alienLaserShootInterval =0.35;
	float timeLastAlienFired;

	MysteryShip mysteryShip;
	float mysteryShipSpawnInterval;
	float timeLastSpawn;

	void CheckForCollisions();


	void GameOver();

	void Reset();
	void InitGame();

	void CheckForHighScore();
	void SaveHighscoreToFile(int highscore);
	int LoadHighscoreFromFile();

	Sound explosionSound;
};