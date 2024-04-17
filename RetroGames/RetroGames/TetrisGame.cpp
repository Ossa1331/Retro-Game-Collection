#include <iostream>
#include<TetrisGame.h>

double lastUpdateTimeTetris = 0;

bool EventTriggered(double interval) {
	double currentTime = GetTime();

	if (currentTime - lastUpdateTimeTetris >= interval) {
		lastUpdateTimeTetris = currentTime;

		return true;
	}

	return false;
}


int TetrisGameInitialize() {

	InitWindow(500, 620, "Tetris Game");
	SetTargetFPS(144);
	Font font = LoadFontEx("Font/monogram.ttf", 64, 0 ,0);

	Grid grid = Grid();
	grid.Print();

	TetrisGame game = TetrisGame();

	while (!WindowShouldClose()) {

		UpdateMusicStream(game.music);
		game.HandleInput();

		if (EventTriggered(0.25)) {
			game.MoveBlockDown();
		}
		
		BeginDrawing();
		ClearBackground(darkBlue);
		
		DrawTextEx(font, "Score", { 365,15 }, 38, 2, WHITE);
		DrawTextEx(font, "Next", { 375,175 }, 38, 2, WHITE);
		if (game.gameOver) {
			DrawTextEx(font, "GAME OVER", { 320,450 }, 38, 2, WHITE);
		}
		DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, lightBlueColor);

		char scoreText[10];
		sprintf_s(scoreText, "%d", game.score); 
		Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

		DrawTextEx(font, scoreText, { 320+ (170-textSize.x)/2,65}, 38, 2, WHITE);
		DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, lightBlueColor);
		game.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}