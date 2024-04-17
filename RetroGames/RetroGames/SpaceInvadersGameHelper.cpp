#include "spaceinvadersgame.hpp"
#include<iostream>
#include<fstream>

SpaceInvadersGame::SpaceInvadersGame() {
	
	music = LoadMusicStream("Sounds/Spacemusic.ogg");
	explosionSound = LoadSound("Sounds/explosion.ogg");
	PlayMusicStream(music);
	InitGame();
}

SpaceInvadersGame::~SpaceInvadersGame() {
	Alien::UnloadImages();
	UnloadMusicStream(music);
	UnloadSound(explosionSound);
}

void SpaceInvadersGame::UpdateSpaceInvaders() {
	if (run) {
		for (auto& laser : spaceship.lasers) {
			laser.UpdateLaser();
		}
		double currentTime = GetTime();
		if (currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
			mysteryShip.SpawnMysteryShip();
			timeLastSpawn = GetTime();
			mysteryShipSpawnInterval = GetRandomValue(10, 20);
		}

		MoveAliens();

		AlienShootLaser();

		for (auto& laser : alienLasers) {
			laser.UpdateLaser();
		}


		DeleteInactiveLasers();

		mysteryShip.UpdateMysteryShip();

		CheckForCollisions();
	}else
		if (IsKeyDown(KEY_ENTER)) {
			Reset();
			InitGame();
		}
	
}
void SpaceInvadersGame::DrawSpaceInvaders() {
	spaceship.DrawSpaceship();

	for (auto& laser : spaceship.lasers) {
		laser.DrawLaser();
	};

	for (auto& obstacle : obstacles) {
		obstacle.DrawObstacle();
	}
	for (auto& alien : aliens) {
		alien.DrawAlien();
	}

	for (auto& laser : alienLasers) {
		laser.DrawLaser();
	}

	mysteryShip.DrawMysteryShip();
}
void SpaceInvadersGame::HandleInputSpaceInvaders() {
	if (run) {
		if (IsKeyDown(KEY_LEFT)) {
			spaceship.MoveLeft();
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			spaceship.MoveRight();
		}
		else if (IsKeyDown(KEY_SPACE)) {
			spaceship.FireLaser();
		}
	}
	
}

void SpaceInvadersGame::DeleteInactiveLasers() {

	for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
		if (!it->active) {
			it = spaceship.lasers.erase(it);
		}
		else {
			++it;
		}
	}
	for (auto it = alienLasers.begin(); it != alienLasers.end();) {
		if (!it->active) {
			it = alienLasers.erase(it);
		}
		else {
			++it;
		}
	}
}

std::vector<Obstacle> SpaceInvadersGame::CreateObstacles() {

	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

	for (int i = 0; i < 4; i++) {
		float offsetX = (i + 1) * gap + i * obstacleWidth;
		obstacles.push_back(Obstacle({ offsetX,float(GetScreenHeight() - 200) }));
	}
	return obstacles;
}

std::vector<Alien> SpaceInvadersGame::CreateAliens()
{
	 std::vector<Alien> aliens;

	 for (int row = 0; row < 5; row++) {
		 for (int column = 0; column < 11; column++) {
			 int alienType;
			 if (row == 0) {
				 alienType = 3;
			 }
			 else if (row == 1 || row == 2) {
				 alienType = 2;
			 }
			 else {
				 alienType = 1;
			 }
			 float x = 75+column * 55; 
			 float y = 110+row * 55;

			 aliens.push_back(Alien(alienType, { x,y }));
		 }
	 }
	 return aliens;
}

void SpaceInvadersGame::MoveAliens() {
	for (auto& alien : aliens) {
		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth()-25) {
			aliensDirection= - 1;
			MoveDownAliens(4);
		}
		else if (alien.position.x < 25) {
			aliensDirection = 1;
			MoveDownAliens(4);
		}
		alien.UpdateAlien(aliensDirection);
	}
}

void SpaceInvadersGame::MoveDownAliens(int distance)
{
	for (auto& alien : aliens) {
		alien.position.y += distance;
	}
}

void SpaceInvadersGame::AlienShootLaser()
{
	double currentTime = GetTime();

	if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
		int randomIndex = GetRandomValue(0, aliens.size() - 1);
		Alien& alien = aliens[randomIndex];
		alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2,
									alien.position.y + alien.alienImages[alien.type].height }, 6));

		timeLastAlienFired = GetTime();
	}

	
}

void SpaceInvadersGame::CheckForCollisions()
{
	//Spaceship lasers

	for (auto& laser : spaceship.lasers) {
		auto it = aliens.begin();
		while (it != aliens.end()) {
			if (CheckCollisionRecs(it->GetRect(), laser.GetRect())) {
				PlaySound(explosionSound);
				if (it->type == 1) {
					score += 100;
				}
				else if (it->type == 2) {
					score += 200;
				}
				else if (it->type == 3) {
					score += 300;
				}
				CheckForHighScore();
				it = aliens.erase(it);
				laser.active = false;
			}
			else {
				++it;
			}
		}
		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), laser.GetRect())) {
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else {
					++it;
				}
			}
		}
		if (CheckCollisionRecs(mysteryShip.GetRect(), laser.GetRect())) {
			mysteryShip.alive = false;
			laser.active = false;
			score += 500;
			CheckForHighScore();
			PlaySound(explosionSound);
		}
	}

	//Alien lasers

	for (auto& laser : alienLasers) {
		if (CheckCollisionRecs(laser.GetRect(), spaceship.getRect())) {
			laser.active = false;
			lives--;
			if (lives == 0) {
				GameOver();
			}
		}

		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), laser.GetRect())) {
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else {
					++it;
				}
			}
		}

	}
	//Alien collision with obstacles

	for (auto& alien : aliens) {
		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), alien.GetRect())) {
					it = obstacle.blocks.erase(it);
				}
				else {
					it++;
				}
			}
		}
		if (CheckCollisionRecs(alien.GetRect(), spaceship.getRect())) {
			GameOver();
		}
	}
	
}

void SpaceInvadersGame::GameOver() {

	run = false;
}

void SpaceInvadersGame::Reset()
{
	spaceship.Reset();
	aliens.clear();
	alienLasers.clear();
	obstacles.clear();
}

void SpaceInvadersGame::InitGame()
{
	obstacles = CreateObstacles();
	aliens = CreateAliens();
	aliensDirection = 1;
	timeLastAlienFired = 0;

	timeLastSpawn = 0;
	mysteryShipSpawnInterval = GetRandomValue(10, 20);

	lives = 3;

	run = true;
	score = 0;

	highscore = LoadHighscoreFromFile();
}

void SpaceInvadersGame::CheckForHighScore()
{
	if (score > highscore) {
		highscore = score;
		SaveHighscoreToFile(highscore);
	}
}

void SpaceInvadersGame::SaveHighscoreToFile(int highscore)
{
	std::ofstream highscoreFile("highscore.txt");
	if (highscoreFile.is_open()) {
		highscoreFile << highscore;
		highscoreFile.close();
	}
	else {
		std::cerr << "Failed to save highscore to file" << std::endl;
	}
}

int SpaceInvadersGame::LoadHighscoreFromFile()
{
	int loadedHighscore = 0;

	std::ifstream highscoreFile("highscore.txt");

	if (highscoreFile.is_open()) {
		highscoreFile >> loadedHighscore;
		highscoreFile.close();
	}
	else {
		std::cerr << "Failed to load highscore from file" << std::endl;
	}
	return loadedHighscore;
}
