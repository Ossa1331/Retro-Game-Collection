#include "TetrisGame.h"
#include <random>

TetrisGame::TetrisGame() {
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();

	gameOver = false;
	score = 0;

	InitAudioDevice();
	music = LoadMusicStream("Sounds/music.mp3");

	PlayMusicStream(music);

	rotateSound = LoadSound("Sounds/rotate.mp3");
	clearSound = LoadSound("Sounds/clear.mp3");

}
TetrisGame::~TetrisGame() {

	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}
Block TetrisGame::GetRandomBlock() {

	if (blocks.empty()) {
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);

	return block;
}

std::vector<Block> TetrisGame::GetAllBlocks() {

	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void TetrisGame::Draw() {
	grid.Draw();
	currentBlock.Draw(11,11);

	switch (nextBlock.id) {
	case 3:
		nextBlock.Draw(255, 290);
		break;
	case 4:
		nextBlock.Draw(255,280);
		break;
	default:
		nextBlock.Draw(270, 270);
		break;
	}
	
}

void TetrisGame::HandleInput() {
	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0) {

		gameOver = false;
		ResetTetris();
	}
	switch (keyPressed) {
		case (KEY_LEFT):
			MoveBlockLeft();
			break;
		case (KEY_A):
			MoveBlockLeft();
			break;
		case (KEY_RIGHT):
			MoveBlockRight();
			break;
		case (KEY_D):
			MoveBlockRight();
			break;
		case (KEY_DOWN):
			MoveBlockDown();
			UpdateScore(0, 1);
			break;
		case (KEY_S):
			MoveBlockDown();
			UpdateScore(0, 1);
			break;
		case(KEY_UP):
			RotateBlock();
			break;
		case(KEY_W):
			RotateBlock();
			break;
	}
}

void TetrisGame::MoveBlockLeft() {

	if (!gameOver) {
		currentBlock.Move(0, -1);

		if (IsBlockOutside() || !BlockFits()) {
			currentBlock.Move(0, 1);
		}
	}

}
void TetrisGame::MoveBlockRight() {

	if (!gameOver) {
		currentBlock.Move(0, 1);

		if (IsBlockOutside() || !BlockFits()) {
			currentBlock.Move(0, -1);
		}
	}
	
}
void TetrisGame::MoveBlockDown() {

	if (!gameOver) {
		currentBlock.Move(1, 0);

		if (IsBlockOutside() || !BlockFits()) {
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
	
}

bool TetrisGame::IsBlockOutside() {
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.IsCellOutside(item.row, item.column)) {
			return true;
		}
	}
	return false;
}

void TetrisGame::RotateBlock() {
	if (!gameOver) {
		currentBlock.Rotate();

		if (IsBlockOutside() || !BlockFits()) {
			currentBlock.UndoRotation();
		}
		else {
			PlaySound(rotateSound);
		}
	}
	
}

void TetrisGame::LockBlock() {

	std::vector<Position> tiles = currentBlock.GetCellPositions();

	for (Position item : tiles) {
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (!BlockFits()) {
		gameOver = true;
	}
	nextBlock = GetRandomBlock();
	int rowsCleared= grid.ClearFullRows();
	if (rowsCleared > 0) {
		PlaySound(clearSound);
		UpdateScore(rowsCleared, 0);
	}
	UpdateScore(rowsCleared, 0);
}

bool TetrisGame::BlockFits() {
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (!grid.IsCellEmpty(item.row, item.column)) {
			return false;
		}
	}
	return true;
}
void TetrisGame::ResetTetris() {

	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	currentBlock = GetRandomBlock();

	score = 0;
}

void TetrisGame::UpdateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared) {
		case 1:
			score += 100;
			break;
		case 2:
			score += 300;
			break;
		case 3: 
			score += 500;
			break;
		default:
			break;
	}

	score += moveDownPoints;
}


