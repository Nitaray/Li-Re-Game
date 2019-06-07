#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <main.h>

void Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Failed to initialized video\n");
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		printf("Failed to initialized PNG\n");
		return false;
	}

	Window = SDL_CreateWindow("Li:Re",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI, SDL_WINDOW_RESIZABLE);

	if (Window == NULL)
	{
		printf("Failed to initialized window\n");
		return false;
	}

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (Renderer == NULL)
	{
		printf("Failed to initialized renderer\n");
		return false;
	}

	icon = IMG_Load("assets/icon.png");
	if (icon)
		SDL_SetWindowIcon(Window, icon);
	else
		printf("Failed to load icon\n");
	SDL_DestroyTexture(icon);

	isRunning = true;
}

void InitializeBoard()
{
	for (int i = 0; i < 49; i++)
	{
		Board[i].x = 100 * i % 700 + 100;
		Board[i].y = i / 7 * 100 + 100;
	}
	BoardItems[1].x = 1049; BoardItems[1].y = 99; BoardItems[1].type = 0;
	BoardItems[2].x = 1049; BoardItems[2].y = 299; BoardItems[2].type = 0;
	BoardItems[3].x = 1049; BoardItems[3].y = 499; BoardItems[3].type = 0;

	SelectedTile.rect.h = 100;
	SelectedTile.rect.w = 100;
}

void InitializeLaser()
{
	LaserDot.R = 255;
	LaserDot.B = 0;
	LaserDot.G = 0;
	LaserDot.rect.w = 5;
	LaserDot.rect.h = 5;
	LaserDot.velX = 0;
	LaserDot.velY = 0;
}

void Finalize()
{
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
}
