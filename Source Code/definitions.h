#pragma once
#define GRID_ROWS 10
#define GRID_COLUMNS 10
#define FINISHED_GAME 1
#define UNFINISHED_GAME 0

typedef struct {
	int x;
	int y;
} POSITION;

typedef struct {
	char initial;
	int holes;
	int hits;
	POSITION* spots;
} SHIP;

typedef struct {
	char grid[GRID_ROWS][GRID_COLUMNS];
	int status;	// 1: finished	0: not finished
	int score;
	SHIP ships[5]; // array of 5 ships
	int floatingShips; // should start with 5 or number of initial ships
} GAME;
