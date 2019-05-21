#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <Structs.h>



const int WIDTH = 1280, HEIGHT = 768;
SDL_Window *Window = NULL;
SDL_Renderer *Renderer = NULL;
SDL_Event event;
SDL_Surface *icon;
Stage Information, Menu, CurrentStage;
Stage Level1, Level2, Level3;
Box LaserDot, SelectedTile;
Box LaserBeam[50 + 7], needRendering[49 + 7];
Tile Board[49 + 7];
Tile BoardItems[10 + 7];
bool isRunning;
bool levelPassed = false;
bool Selecting = false;
bool laserRunning = false;
int Selection, renderItems = 0;



int main(int argc, char *argv[])
{
	Initialize();
	InitializeBoard();
	loadData();
	loadStage(Menu, true);
	while (isRunning)
	{
			if (CurrentStage.Number > 10)
			{
				updateLaser();
				renderFrame();
			}
			SDL_RenderPresent(Renderer);
			PollEvent();
	}
	Finalize();
	return 0;
}