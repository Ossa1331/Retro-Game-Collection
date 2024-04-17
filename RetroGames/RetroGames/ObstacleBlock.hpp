#pragma once

#include<raylib.h>

class ObstacleBlock {
public:
	ObstacleBlock(Vector2 position);
	void DrawBlock();
	Rectangle getRect();
private:
	Vector2 position;
};