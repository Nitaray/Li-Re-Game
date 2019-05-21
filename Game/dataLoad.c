#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <Structs.h>
#include <main.h>

void loadData()
{
	Menu.Number = 1;
	strcpy(Menu.ID, "assets/Menu.png");

	Information.Number = 2;
	strcpy(Information.ID, "assets/InformationTab.png");

	LaserDot.R = 255;
	LaserDot.B = 0;
	LaserDot.G = 0;
	LaserDot.rect.x = CurrentStage.startX;
	LaserDot.rect.y = CurrentStage.startY;
	LaserDot.rect.w = 5;
	LaserDot.rect.h = 5;
	LaserDot.velX = 0;
	LaserDot.velY = 0;

	SelectedTile.rect.h = 100;
	SelectedTile.rect.w = 100;

	Level1.Number = 11;
	Level1.startX = 100 - 5;
	Level1.startY = 400 - 5;
	Level1.endX = 700 - 5;
	Level1.endY = 400 - 5;
	strcpy(Level1.ID, "assets/Level1.png");
	for (int i = 0; i < 49; i++)
		Level1.tileType[i] = 0;
	for (int i = 21; i < 28; i++)
		Level1.tileType[i] = 1;

	Level2.Number = 12;
	Level2.startX = 100 - 5;
	Level2.startY = 400 - 5;
	Level2.endX = 700 - 5;
	Level2.endY = 400 - 5;
	strcpy(Level2.ID, "assets/Level2.png");
	for (int i = 0; i < 49; i++)
		Level2.tileType[i] = 0;
	for (int i = 21; i < 28; i++)
		Level2.tileType[i] = 1;
	Level2.tileType[23] = 2;
	Level2.tileType[37] = 2;
	Level2.tileType[39] = 3;
	Level2.tileType[30] = 1;
	Level2.tileType[32] = 1;
	Level2.tileType[38] = 1;
	Level2.tileType[24] = 0;
	Level2.items[1] = 3; Level2.itemcounts[1] = 1;
	Level2.items[2] = 0; Level2.itemcounts[2] = 0;
	Level2.items[3] = 0; Level2.itemcounts[3] = 0;

	Level3.Number = 13;
	Level3.startX = 100 - 5;
	Level3.startY = 100 - 5;
	Level3.endX = 700 - 5;
	Level3.endY = 600 - 5;
	strcpy(Level3.ID, "assets/Level3.png");
	for (int i = 0; i < 49; i++)
		Level3.tileType[i] = 1;
	Level3.tileType[3] = 0;
	Level3.tileType[7] = 0;
	Level3.tileType[8] = 0;
	Level3.tileType[10] = 0;
	Level3.tileType[12] = 0;
	Level3.tileType[14] = 0;
	Level3.tileType[21] = 0;
	Level3.tileType[24] = 0;
	Level3.tileType[26] = 0;
	Level3.tileType[28] = 0;
	Level3.tileType[33] = 0;
	Level3.tileType[35] = 0;
	Level3.tileType[37] = 0;
	Level3.tileType[38] = 0;
	Level3.tileType[40] = 0;
	Level3.tileType[42] = 0;
	Level3.tileType[47] = 0;
	Level3.tileType[48] = 0;
	Level3.tileType[2] = 2;
	Level3.tileType[43] = 2;
	Level3.tileType[18] = 3;
	Level3.items[1] = 3; Level3.itemcounts[1] = 3;
	Level3.items[2] = 2; Level3.itemcounts[2] = 1;
	Level3.items[3] = 0; Level3.itemcounts[3] = 0; 
}
