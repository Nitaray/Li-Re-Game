#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <Structs.h>
#include <main.h>
#include <math.h>

double dist(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void resetLaser()
{
	LaserDot.rect.x = CurrentStage.startX;
	LaserDot.rect.y = CurrentStage.startY;
	LaserDot.velX = 0;
	LaserDot.velY = 0;
}

void loadStage(Stage stage, bool reset)
{
	SDL_Texture *img = IMG_LoadTexture(Renderer, stage.ID);
	if (img)
		SDL_RenderCopy(Renderer, img, NULL, NULL);
	SDL_DestroyTexture(img);
	if (stage.Number != 0)
		CurrentStage = stage;
	if (reset)
	{
		resetLaser();
		levelPassed = false;
		for (int i = 0; i < 49; i++)
			Board[i].type = stage.tileType[i];
		for (int i = 1; i <= 3; i++)
		{
			BoardItems[i].type = stage.items[i];
			BoardItems[i].typecounts = stage.itemcounts[i];
		}
		renderItems = 0;
	}
}

void loadRect(Box A)
{
	SDL_SetRenderDrawColor(Renderer, A.R, A.B, A.G, 255);
	SDL_RenderFillRect(Renderer, &A.rect);
}

void HandleMouseClick(int x, int y)
{
	switch (event.button.button)
	{
	case SDL_BUTTON_LEFT:
		if (Selecting)
		{
			for (int i = 0; i < 49; i++)
			{
				if ((abs(x - Board[i].x) <= 50 && abs(y - Board[i].y) <= 50) && Board[i].type != 0)
				{
					Board[i].type = CurrentStage.items[Selection];
					//printf("Type Changed %d\n", i);
					needRendering[renderItems].rect.x = Board[i].x - 50;
					needRendering[renderItems].rect.y = Board[i].y - 50;
					needRendering[renderItems].rect.w = 100;
					needRendering[renderItems].rect.h = 100;
					strcpy(needRendering[renderItems].path, SelectedTile.path);
					renderItems++;
				}
			}
			Selecting = false;
		}
		break;
	case SDL_BUTTON_RIGHT:
		loadStage(CurrentStage, true);
		break;
	}

	switch (CurrentStage.Number)
	{
	case 1:
		loadStage(Level1, true);
		printf("Loading level 1\n");
		break;
	case 11:
		if (levelPassed)
			loadStage(Level2, true);
			printf("Loading level 2\n");
		break;
	case 12:
		if (levelPassed)
		{
			loadStage(Level3, true);
			printf("Loading level 3\n");
		}
		else
		{
			for (int i = 1; i <= 3; i++)
				if ((abs(x - BoardItems[i].x) <= 50) && (abs(y - BoardItems[i].y) <= 50) 
					&& !laserRunning 
					&& CurrentStage.items[i] != 0 && BoardItems[i].typecounts > 0)
				{
					Selection = i;
					Selecting = true;
					BoardItems[i].typecounts--;
					printf("Selecting %d\n", Selection);
				}
		}
		break;
	case 13:
		if (levelPassed)
		{
			loadStage(Menu, true);
			printf("End of demo. Thanks for playing!");
		}
		else
		{
			for (int i = 1; i <= 3; i++)
				if ((abs(x - BoardItems[i].x) <= 50) && (abs(y - BoardItems[i].y) <= 50)
					&& !laserRunning
					&& CurrentStage.items[i] != 0 && BoardItems[i].typecounts > 0)
				{
					Selection = i;
					Selecting = true;
					BoardItems[i].typecounts--;
					printf("Selecting %d\n", Selection);
				}
		}
		break;
	}
}

void hitDetection(int x, int y, int velx, int vely)
{
	if (x + velx <= 750 && x + velx >= 50 && y + vely <= 750 && y + vely >= 50)
	{
		LaserDot.rect.x += LaserDot.velX;
		LaserDot.rect.y += LaserDot.velY;
		x = LaserDot.rect.x;
		y = LaserDot.rect.y;
	}
	else
	{
		resetLaser();
		printf("Out of Bound\n");
	}
	if (x == CurrentStage.endX && y == CurrentStage.endY)
	{
		levelPassed = true;
		resetLaser();
		printf("Level Passed\n");
	}
	for (int i = 0; i < 49; i++)
	{
		switch (Board[i].type)
		{
		case 0:
			if (velx < 0 || vely < 0)
			{
				if ((abs(x - Board[i].x) < 50) && (abs(y - Board[i].y) < 50))
				{
					resetLaser();
					//printf("Wall hit %d %d\n", i, Board[i].type);
					printf("Wall hit\n");
				}
			}
			else
			{
				if ((abs(x - Board[i].x) <= 50) && (abs(y - Board[i].y) <= 50))
				{
					resetLaser();
					//printf("Wall hit %d %d\n", i, Board[i].type);
					printf("Wall hit\n");
				}
			}
			break;
		case 2:
			if (x == Board[i].x -5 && y == Board[i].y - 5)
			{
				printf("Mirror hit\n");
				LaserDot.velX += LaserDot.velY;
				LaserDot.velY = LaserDot.velX - LaserDot.velY;
				LaserDot.velX = LaserDot.velX - LaserDot.velY;
			}
			break;
		case 3:
			if (x == Board[i].x - 5 && y == Board[i].y - 5)
			{
				printf("Mirror hit\n");
				LaserDot.velX += LaserDot.velY;
				LaserDot.velY = LaserDot.velX - LaserDot.velY;
				LaserDot.velX = LaserDot.velX - LaserDot.velY;
				LaserDot.velX *= -1;
				LaserDot.velY *= -1;
			}
			break;
		}
	}
}

void updateLaser()
{
	hitDetection(LaserDot.rect.x, LaserDot.rect.y, LaserDot.velX, LaserDot.velY);
	//printf("%d %d\n", LaserDot.rect.x, LaserDot.rect.y);
	LaserBeam[25] = LaserDot;
	for (int i = 0; i < 25; i++)
	{
		LaserBeam[i] = LaserBeam[i + 1];
	}
	if (LaserDot.velX != 0 || LaserDot.velY != 0)
	{
		laserRunning = true;
		Selecting = false;
	}
	else
		laserRunning = false;
}

void renderFrame()
{
	loadStage(CurrentStage, false);

	for (int i = 0; i < renderItems; i++)
	{
		SDL_Texture *img = IMG_LoadTexture(Renderer, needRendering[i].path);
		if (img)
			SDL_RenderCopy(Renderer, img, NULL, &needRendering[i].rect);
		SDL_DestroyTexture(img);
	}

	if (Selecting)
	{
		switch (CurrentStage.items[Selection])
		{
		case 1:
			strcpy(SelectedTile.path, "assets/Path.png");
			break;
		case 2:
			strcpy(SelectedTile.path, "assets/MirrorLeft.png");
			break;
		case 3:
			strcpy(SelectedTile.path, "assets/MirrorRight.png");
			break;
		}
		SelectedTile.rect.x = event.motion.x - 50;
		SelectedTile.rect.y = event.motion.y - 50;
		SDL_Texture *img = IMG_LoadTexture(Renderer, SelectedTile.path);
		if (img)
			SDL_RenderCopy(Renderer, img, NULL, &SelectedTile.rect);
		SDL_DestroyTexture(img);
	}
	else
	{
		loadRect(LaserDot);
		for (int i = 0; i < 25; i++)
			loadRect(LaserBeam[i]);
	}


}

void PollEvent()
{
	if (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				loadStage(Menu, true);
				break;
			default:
				if (CurrentStage.Number > 10 && !laserRunning)
					switch (event.key.keysym.sym)
					{
					case SDLK_RIGHT:
						LaserDot.velX = 5;
						LaserDot.velY = 0;
						break;
					case SDLK_LEFT:
						LaserDot.velX = -5;
						LaserDot.velY = 0;
						break;
					case SDLK_UP:
						LaserDot.velX = 0;
						LaserDot.velY = -5;
						break;
					case SDLK_DOWN:
						LaserDot.velX = 0;
						LaserDot.velY = 5;
						break;
					}
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			HandleMouseClick(event.motion.x, event.motion.y);
		}
}

