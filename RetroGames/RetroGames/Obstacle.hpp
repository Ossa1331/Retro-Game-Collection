#pragma once
#include<vector>
#include<ObstacleBlock.hpp>

class Obstacle {
public:
	Obstacle(Vector2 position);
	void DrawObstacle();
	Vector2 position;
	std::vector<ObstacleBlock> blocks;
	static std::vector<std::vector<int>>grid;
private:

};