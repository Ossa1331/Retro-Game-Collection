#include<raylib.h>
#include<Colors.h>
#include<spaceinvadersgame.hpp>
#include<String>

std::string FormatWithLeadingZeros(int number, int width) {
	std::string numberText = std::to_string(number);

	int leadingZeros = width - numberText.length();
	return numberText = std::string(leadingZeros, '0') + numberText;
}

int main() {
	int offset = 50;
	int screenWidth = 750;
	int screenHeight = 700;

	InitWindow(screenWidth+ offset,screenHeight+ 2*offset, "Space Invaders");
	InitAudioDevice();
	
	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
	Texture2D spaceshipImage = LoadTexture("Images/spaceship.png");

	SetTargetFPS(144);
	
	SpaceInvadersGame spaceInvadersGame;
	

	while (!WindowShouldClose()) {

		UpdateMusicStream(spaceInvadersGame.music);
	
		spaceInvadersGame.HandleInputSpaceInvaders();
		spaceInvadersGame.UpdateSpaceInvaders();

		BeginDrawing();
		ClearBackground(darkGreyColor2);
		DrawRectangleRoundedLines({ 10,10,780,780 }, 0.18f, 20, 2, yellowColor3);
		DrawLineEx({ 25,730 }, { 775,730 }, 3, yellowColor3);
		if (spaceInvadersGame.run) {
			DrawTextEx(font, "LEVEL 01", { 570, 740 }, 34, 2, yellowColor3);
		}
		else {
			DrawTextEx(font, "GAME OVER", { 570, 740 }, 34, 2, yellowColor3);
		}

		float x = 50.0;

		for (int i = 0; i < spaceInvadersGame.lives; i++) {
			DrawTextureV(spaceshipImage, { x,745 }, WHITE);
			x += 50;
		}

		DrawTextEx(font, "SCORE", { 50, 15 }, 34, 2, yellowColor3);
		std::string scoreText = FormatWithLeadingZeros(spaceInvadersGame.score, 5);
		DrawTextEx(font, scoreText.c_str(), { 50,40 }, 34, 2, yellowColor3);

		DrawTextEx(font, "HIGH-SCORE", { 570, 15 }, 34, 2, yellowColor3);
		std::string highscoreText = FormatWithLeadingZeros(spaceInvadersGame.highscore, 5);
		DrawTextEx(font, highscoreText.c_str(), { 655,40 }, 34, 2, yellowColor3);

		spaceInvadersGame.DrawSpaceInvaders();
		
		
		
		EndDrawing();
	}


	CloseWindow();
	CloseAudioDevice();
}