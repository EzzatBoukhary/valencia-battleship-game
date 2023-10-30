#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "definitions.h"

void createGrid(GAME* battleshipGame);
void placeShip(char grid[][GRID_COLUMNS], SHIP* ship);

void createGrid(GAME* battleshipGame)
{
	SHIP seminoleStateShip, airForceAcademy, valeniaDestroyer, eskimoUniversity, delandHighSchool;

	char shipInitial;
	int shipSize;

	for (int row = 0; row < GRID_ROWS; row++)
	{
		for(int col = 0; col < GRID_COLUMNS; col++)
			battleshipGame->grid[row][col] = 0;
	}
	battleshipGame->score = 0;
	battleshipGame->status= UNFINISHED_GAME;
	battleshipGame->floatingShips = 5;

	// 1. (S) Seminole State Ship (3 Holes)
	seminoleStateShip.holes = 3;
	seminoleStateShip.hits = 0;
	seminoleStateShip.initial = 'S';
	seminoleStateShip.spots = malloc(seminoleStateShip.holes * sizeof(POSITION)); // MAKE SURE TO FREE THESE!!!!
	placeShip(battleshipGame->grid, &seminoleStateShip);
	battleshipGame->ships[0] = seminoleStateShip;

	// 2. (A) Air Force Academy (5 Holes)
	airForceAcademy.holes = 5;
	airForceAcademy.hits = 0;
	airForceAcademy.initial = 'A';
	airForceAcademy.spots = malloc(airForceAcademy.holes * sizeof(POSITION));
	placeShip(battleshipGame->grid, &airForceAcademy);
	battleshipGame->ships[1] = airForceAcademy;

	// 3. (V) Valencia Destroyer (4 Holes)
	valeniaDestroyer.holes = 4;
	valeniaDestroyer.hits = 0;
	valeniaDestroyer.initial = 'V';
	valeniaDestroyer.spots = malloc(valeniaDestroyer.holes * sizeof(POSITION));
	placeShip(battleshipGame->grid, &valeniaDestroyer);
	battleshipGame->ships[2] = valeniaDestroyer;

	// 4. (E) Eskimo University (3 Holes)
	eskimoUniversity.holes = 3;
	eskimoUniversity.hits = 0;
	eskimoUniversity.initial = 'E';
	eskimoUniversity.spots = malloc(eskimoUniversity.holes * sizeof(POSITION));
	placeShip(battleshipGame->grid, &eskimoUniversity);
	battleshipGame->ships[3] = eskimoUniversity;

	// 5. (D) Deland High School (2 Holes)
	delandHighSchool.holes = 2;
	delandHighSchool.hits = 0;
	delandHighSchool.initial = 'D';
	delandHighSchool.spots = malloc(delandHighSchool.holes * sizeof(POSITION));
	placeShip(battleshipGame->grid, &delandHighSchool);
	battleshipGame->ships[4] = delandHighSchool;

}
void placeShip(char grid[][GRID_COLUMNS], SHIP* ship)
{
	int randomNumber, x, y;
	int flag = 0;
	int noHorizontal = 0;
	int noVertical = 0;
	int i;

#pragma region Getting_Starting_Point
	do
	{
		srand(time(NULL));
		x = 0 + rand() % (9 - 0);
		y = 10 + rand() % (19 - 10);
		y -= 10;

		noHorizontal = 0;
		noVertical = 0;
		flag = 0;

		if (grid[x][y] == 0)	// starting point is free
		{
			for (i = 1; i < (*ship).holes; i++)
			{

				if (x + i >= GRID_COLUMNS || grid[x + i][y] != 0) // no space to the right of the point?
					noHorizontal = 1;

				if (y + i >= GRID_COLUMNS || grid[x][y + i] != 0) // no space below the point?
					noVertical = 1;
			}
			if (noHorizontal && noVertical) // no space around the point?
				flag = 1;
		}
		else
			flag = 1;
	} while (flag); // keep randomizing points if there's no space for the ship around it
#pragma endregion

#pragma region Ship_Placement
	grid[x][y] = (*ship).initial;

	if (noHorizontal) // if no horizontal space
	{
		// Assign ship initials on the grid downwards from starting point
		for (i = 0; i < (*ship).holes; i++)
		{
			grid[x][y + i] = (*ship).initial;
			(*ship).spots[i].x = x;
			(*ship).spots[i].y = y + i;
		}
	}
	else if (noVertical) // if no vertical space
	{
		// Assign ship initials on the grid to the right of starting point
		for (i = 0; i < (*ship).holes; i++)
		{
			grid[x + i][y] = (*ship).initial;
			(*ship).spots[i].x = x + i;
			(*ship).spots[i].y = y;
		}
	}
	else
	{
		srand(time(NULL));
		randomNumber = rand() % 2 + 1;	// 1 - 2

		if (randomNumber == 1) // 1 -> go down
			for (i = 0; i < (*ship).holes; i++)
			{
				grid[x][y + i] = (*ship).initial;
				(*ship).spots[i].x = x;
				(*ship).spots[i].y = y + i;
			}

		else if (randomNumber == 2) // 2 -> go right
			for (i = 0; i < (*ship).holes; i++)
			{
				grid[x + i][y] = (*ship).initial;
				(*ship).spots[i].x = x + i;
				(*ship).spots[i].y = y;
			}
	}
#pragma endregion
}