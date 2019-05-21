#pragma once
#include <SDL.h>

typedef struct Stage
{
	int Number;
	char ID[256 + 7];
	SDL_Rect pos;
	int startX;
	int startY;
	int endX;
	int endY;
	int tileType[49 + 7];
	int items[10 + 7];
	int itemcounts[10 + 7];
} Stage;

typedef struct Tile
{
	int x;
	int y;
	int type; 
	int typecounts;
} Tile;

typedef struct Box
{
	SDL_Rect rect;
	int R;
	int G;
	int B; 
	int a;
	int velX;
	int velY;
	char path[32 + 7];
} Box;