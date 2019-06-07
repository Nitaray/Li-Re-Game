#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <Structs.h>

extern const int WIDTH, HEIGHT;
extern SDL_Window* Window;
extern SDL_Renderer* Renderer;
extern SDL_Event event;
extern SDL_Surface* icon;
extern SDL_Texture* TxtureContent[10 + 7];
extern Stage Stages[30 + 7];
extern Box LaserDot, SelectedTile;
extern Box LaserBeam[50 + 7], needRendering[49 + 7];
extern bool isRunning;
extern bool levelPassed;
extern bool Selecting;
extern bool laserRunning;
extern Tile Board[49 + 7];
extern Tile BoardItems[10 + 7];
extern int Selection, renderItems, CurrentStage;