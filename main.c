/*
Programmer's Name: Ezzat Boukhary
Date: 05/12/2022
Valencia BattleShip Game
A console-based game based on the classic Battleships board game.

TO-DO: display top 10 best scores descending order in console + txt file
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "creatingBoard.h"

char mainMenuInput();
void startGame(GAME* battleshipGame);
void displayBoard(char grid[][GRID_COLUMNS]); //GAME* battleshipGame
int fireMissile(GAME* battleshipGame);

int main()
{
	char choice;
	FILE* gamesData = NULL;
	FILE* topTenScores = NULL;
	GAME battleship;
	battleship.floatingShips = 0;

	do
	{
		choice = mainMenuInput();
		switch (choice)
		{

			/// Start new game ///
		case 'a':
		case 'A':
			printf("Starting game... please wait.\n");
			startGame(&battleship);
			break;

			/// Resume previous game ///
		case 'b':
		case 'B':
			printf("Searching for a previous unfinished game...\n");
			gamesData = fopen("gamesData.bin", "rb");
			if (gamesData != NULL)
			{
				fread(&battleship, sizeof(GAME), 1, gamesData);

				fclose(gamesData);

				printf("Retreived saved game data. Resuming game now...\n");
				startGame(&battleship);

			}
			else
			{
				printf("No previous data was found. Starting a new game from scratch instead...\n");
				startGame(&battleship);
			}
			break;

			/// Top 10 Best scores ///
		case 'c':
		case 'C':

			break;

			/// Quit + save data ///
		case 'd':
		case 'D':

			break;
		default:
			printf("Invalid choice, option not in the menu.\n");
		}
	} while (choice != 'D' && choice != 'd');
	system("pause");
}
char mainMenuInput()
{
	char choice;

	///////   MAIN MENU   ///////
	printf("_________________________________________________________\n");
	printf("| A. Start a new game from scratch.\t\t\t|\n");
	printf("| B. If a previous game was not finished, resumes it.\t|\n");
	printf("| C. Display top 10 best scores.\t\t\t|\n");
	printf("| D. Quit and save data.\t\t\t\t\n");
	printf("|_______________________________________________________|\n");
	printf("\nEnter a choice from the above options: ");

	scanf_s(" %c", &choice);
	return choice;
}
void startGame(GAME* battleshipGame)
{
	int x, y;
	char choice;
	FILE* gameData = NULL;

	// If there is no previo
	if(battleshipGame->floatingShips == 0)
		createGrid(battleshipGame);

	///////   DISPLAY BOARD TO USER   ///////
	displayBoard(battleshipGame->grid);

	///////   IN-GAME MENU   ///////
	do
	{
		printf("________________________________\n");
		printf("| A. Fire Missile\t\t|\n");
		printf("| B. Quit game.\t\t\t|\n");
		printf("| Game Legend:\t\t\t|\n");
		printf("|	H -> Ship Hit\t\t|\n");
		printf("|	M -> Shot Missed\t|\n");
		printf("|	X -> Ship Destroyed\t|\n");
		printf("|_______________________________|\n");
		printf("\nEnter a choice from the above options: ");

		scanf_s(" %c", &choice);
		switch (choice)
		{

			// Fire Missile
		case 'a':
		case 'A':

			if (fireMissile(battleshipGame) == FINISHED_GAME) // game ended
			{
				displayBoard(battleshipGame->grid);
				printf("! ! ! YOU WIN ! ! !\n");
				printf("You destroyed all ships using %i missiles!\n", battleshipGame->score);
				battleshipGame->status = FINISHED_GAME; // marks game as finished
			}
			else
			{
				displayBoard(battleshipGame->grid);
			}
			break;

			// Quit
		case 'b':
		case 'B':
			// Opening bin file for writing
			gameData = fopen("gamesData.bin", "wb");

			if (gameData == NULL)
			{
				printf("The file used for saving games couldn't be opened. Going back to main menu...\n");
				return;
			}

			// Copy game data to bin file
			fwrite(battleshipGame, sizeof(GAME), 1, gameData);

			fclose(gameData);
			break;
		default:
			printf("Invalid choice, option not in the menu.\n");
		}
	} while (choice != 'B' && choice != 'b' && battleshipGame->status != FINISHED_GAME);

}

void displayBoard(char grid[][GRID_COLUMNS])
{
	int x, y;

	printf("\n   1  2  3  4  5  6  7  8  9  10\n");
	for (y = 0; y < GRID_COLUMNS; y++)
	{
		///////   Print number for rows (y's)   ///////
		if ((y + 1) >= 10)
			printf("%i ", y + 1);
		else
			printf("%i  ", y + 1);


		for (x = 0; x < GRID_ROWS; x++)
		{
			// Display the icons on the board
			switch (grid[x][y])
			{
			case 'H': // Ship Hit
				printf("H  ");
				break;
			case 'X': // Ship destroyed
				printf("X  ");
				break;
			case 'M': // Missed shot
				printf("M  ");
				break;
			default:
				printf("-  ");
				break;
			}
		}
		printf("\n");
	}
	return;
}

int fireMissile(GAME* battleshipGame) // returns a value whether the game ended or not
{
	int x, y;
	SHIP* shotShip = NULL;

	printf("Your current number of missile shots (score) is %i and there are %i remaining ships.\n", battleshipGame->score, battleshipGame->floatingShips);
	do
	{
		///////   GET X POSITION FOR HIT   ///////
		do
		{
			printf("Enter the position on the x-axis (1-10) where you'd like to fire the missile at: ");
			scanf_s("%i", &x);
			x--;
			if (x < 0 || x > 9)
				printf("The number should be between 0 and 10 on the board's x-axis!\n");
		} while (x < 0 || x > 9);


		///////   GET Y POSITION FOR HIT   ///////
		do
		{
			printf("Enter the position on the y-axis (1-10) where you'd like to fire the missile at: ");
			scanf_s("%i", &y);
			y--;
			if (y < 0 || y > 9)
				printf("The number should be between 0 and 10 on the board's y-axis!\n");
		} while (y < 0 || y > 9);

		///////   CHECK IF SPOT IS HIT-ABLE   ///////
		if (battleshipGame->grid[x][y] == 'H' || battleshipGame->grid[x][y] == 'M' || battleshipGame->grid[x][y] == 'X')
			printf("That position was already hit before, try a different spot.\n");

	} while (battleshipGame->grid[x][y] == 'H' || battleshipGame->grid[x][y] == 'M' || battleshipGame->grid[x][y] == 'X');

	///////   CHECK LOCATION  & REGISTER HIT ///////
	battleshipGame->score++;

	if (!battleshipGame->grid[x][y]) // if the spot is empty -> mark as Missed
	{
		battleshipGame->grid[x][y] = 'M';
	}
	else					// not empty (has a ship) -> mark as Hit
	{
		switch (battleshipGame->grid[x][y])
		{
		case 'S':
			shotShip = &battleshipGame->ships[0];
			break;
		case 'A':
			shotShip = &battleshipGame->ships[1];
			break;
		case 'V':
			shotShip = &battleshipGame->ships[2];
			break;
		case 'E':
			shotShip = &battleshipGame->ships[3];
			break;
		case 'D':
			shotShip = &battleshipGame->ships[4];
			break;
		default:
			printf("Something went wrong. No shot ship found :(\n");
			exit(1);
			break;
		}

		(*shotShip).hits++;
		battleshipGame->grid[x][y] = 'H';

		///////   WILL A BOAT SINK? ///////
		if ((*shotShip).hits == (*shotShip).holes)
		{
			for (int i = 0; i < (*shotShip).holes; i++)
			{
				int tempX, tempY;
				tempX = (*shotShip).spots[i].x;
				tempY = (*shotShip).spots[i].y;
				battleshipGame->grid[tempX][tempY] = 'X';
			}
			battleshipGame->floatingShips--;
		}
		if (battleshipGame->floatingShips == 0)
			return FINISHED_GAME; // tell the calling function that the game ended
	}
	return UNFINISHED_GAME;

}
