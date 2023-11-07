# valencia-battleship-game
A console-based game based on the classic Battleships board game. 

Made for a C Programming course project at Valencia College for Spring 2022

# How it is Played
* The player is given a menu to choose between starting a new game, resuming a previous game, listing the top 10 scores (incomplete feature), and quitting.
* Upon starting a new game, the player is presented with a 10x10 grid. The grid contains 5 hidden ships with various sizes.
* The objective is to find and destroy all the ships on the grid with the LEAST number of missiles.

# Data Storage
* If the user quits before completing a game, the program saves the data to a .gamesData.bin file in the program's folder.
* If the user decides to resume the previous game, the program restores the data from the .bin file and resumes the game from the previous state.
* The .bin file gets overwritten every time the user saves an unfinished game.

# Screenshots
![image](https://github.com/EzzatBoukhary/valencia-battleship-game/blob/main/image1.png)
![image](https://github.com/EzzatBoukhary/valencia-battleship-game/blob/main/image2.png)
![image](https://github.com/EzzatBoukhary/valencia-battleship-game/blob/main/image3.png)
