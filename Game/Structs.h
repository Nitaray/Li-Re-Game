#pragma once
#include <SDL.h>

typedef struct Stage
{
	int ID;
	char Name[32 + 7];
	char path[256 + 7];
	int startX, startY;
	int endX, endY;
	int tileType[49 + 7];
	int items[10 + 7];
	int itemcounts[10 + 7];
	SDL_Rect pos;
	SDL_Texture* Txture;

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
	int TxtureID;
} Box;