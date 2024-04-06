#pragma once
#include<grid.h>
#include<blocks.cpp>

class TetrisGame {
public:
	TetrisGame();
	~TetrisGame();

	void Draw();
	void MoveBlockDown();
	void HandleInput();

	bool gameOver;
	int score;

	Music music;

private:
	
	std::vector<Block> GetAllBlocks();
	Grid grid;
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;

	Block GetRandomBlock();
	void MoveBlockLeft();
	void MoveBlockRight();
	bool IsBlockOutside();
	void LockBlock();
	void RotateBlock();
	bool BlockFits();

	void ResetTetris();
	void UpdateScore(int linesCleared, int moveDownPoints);

	Sound rotateSound;
	Sound clearSound;
};