#include <ObstacleBlock.hpp>
#include <Colors.h>

ObstacleBlock::ObstacleBlock(Vector2 position) {
	this->position = position;
}
void ObstacleBlock::DrawBlock() {
	DrawRectangle(position.x, position.y, 3, 3, yellowColor3);
}

Rectangle ObstacleBlock::getRect()
{
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 3;
	rect.height = 3;

	return rect;
}
