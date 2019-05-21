#pragma once
#include <SDL.h>
#include <Structs.h>

extern const int WIDTH, HEIGHT;
extern SDL_Window *Window;
extern SDL_Renderer *Renderer;
extern SDL_Event event;
extern SDL_Surface *icon;
extern Stage Information, Menu, CurrentStage;
extern Stage Level1, Level2, Level3;
extern Box LaserDot, SelectedTile;
extern Box LaserBeam[50 + 7], needRendering[49 + 7];
extern bool isRunning;
extern bool levelPassed;
extern bool Selecting;
extern bool laserRunning;
extern Tile Board[49 + 7];
extern Tile BoardItems[10 + 7];
extern int Selection, renderItems;