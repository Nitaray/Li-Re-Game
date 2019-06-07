#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <main.h>
#include <Structs.h>>

void loadData(Stage* pstage, char* path)
{
	FILE* input = fopen(path, "r");
	if (input == NULL)
		printf("Failed to open %s\n", path);
	int* tile = pstage->tileType;
	int* item = pstage->items;
	int* itemcount = pstage->itemcounts;

	int isLevel;

	fscanf(input, "%d\n", &pstage->ID);		//get ID
	fgets(pstage->Name, 32, input);			//get Name
	fscanf(input, "%s\n", pstage->path);	//get PNG path
	fscanf(input, "%d\n", &isLevel);		//check if playable level to continue

	if (isLevel)
	{
		fscanf(input, "%d %d\n%d %d\n", &pstage->startX, &pstage->startY, &pstage->endX, &pstage->endY);	//Start and End pos of laser

		for (int i = 0; i < 7; i++)
			fscanf(input, "%d %d %d %d %d %d %d\n", &tile[i * 7], &tile[i * 7 + 1], &tile[i * 7 + 2],		//Get level tiles types.
				&tile[i * 7 + 3], &tile[i * 7 + 4], &tile[i * 7 + 5], &tile[i * 7 + 6]);

		int itemTypes;					
		fscanf(input, "%d\n", &itemTypes);	//Get number of different items

		for (int i = 1; i <= itemTypes; i++)
			fscanf(input, "%d %d\n", &item[i], &itemcount[i]);	//Get items type and items count
	}

	fclose(input);
}

void TxtureInit(Stage* pstage)
{
	pstage->Txture = IMG_LoadTexture(Renderer, pstage->path);	
	if (!pstage->Txture)
		printf("Failed to load texture at %s\n", pstage->path);
}

void loadTxtureContent(int ID, char* dpath)
{
	FILE* input = fopen(dpath, "r");
	if (input == NULL)
		printf("Failed to open %s", dpath);
	char path[256 + 7];
	fgets(path, 256, input);
	TxtureContent[ID] = IMG_LoadTexture(Renderer, path);
	if (!TxtureContent[ID])
		printf("Failed to load texture at %s\n", path);
	fclose(input);
}

void dataInit()
{
	loadData(&Stages[1], "data/level/HomeScreen.dat");
	loadData(&Stages[2], "data/level/Info.dat");
	loadData(&Stages[11], "data/level/level1.dat");
	loadData(&Stages[12], "data/level/level2.dat");
	loadData(&Stages[13], "data/level/level3.dat");

	TxtureInit(&Stages[1]);
	TxtureInit(&Stages[2]);
	TxtureInit(&Stages[11]);
	TxtureInit(&Stages[12]);
	TxtureInit(&Stages[13]);

	loadTxtureContent(0, "data/tile/Wall.dat");
	loadTxtureContent(1, "data/tile/Path.dat");
	loadTxtureContent(2, "data/tile/MirrorLeft.dat");
	loadTxtureContent(3, "data/tile/MirrorRight.dat");
}