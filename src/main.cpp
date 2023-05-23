#include <iostream>
#include <ncurses.h>
#include "Player.h"

const int MAZE_NUM_ROWS = 10;
const int MAZE_NUM_COLUMNS = 10;

char maze[MAZE_NUM_ROWS][MAZE_NUM_COLUMNS] = {
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','*'},
    {'.','.','#','.','.','.','.','.','.','.'},
    {'.','.','#','.','.','.','.','.','.','.'},    // @ = player
    {'.','.','#','.','.','.','.','.','.','*'},    // % = goal
    {'.','.','#','.','.','.','.','.','.','.'},    // * = point
    {'.','.','#','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
};

Player player;

const int goalLocationX = 2;
const int goalLocationY = 2;
const char goalIcon = '%';
const char point = '*';

bool isGameOver() {
    return player.playerLocationX == goalLocationX
        && player.playerLocationY == goalLocationY;
}

void movePlayer(int y, int x) {
    if (maze[y][x] == '*') player.points += 1;
    if (maze[y][x] != '#') {
        player.numberOfMoves += 1;
        maze[player.playerLocationY][player.playerLocationX] = '.';
        maze[y][x] = player.playerIcon;
        player.playerLocationY = y;
        player.playerLocationX = x;
    }
}

void setUpMaze() {
    maze[player.playerStartY][player.playerStartX] = player.playerIcon;
    maze[goalLocationY][goalLocationX] = goalIcon;
}

void printMaze() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            printw("%c", maze[y][x]);
        }
        printw("\n");
    }

    printw("@ = player\n");
    printw("%% = goal\n");
    printw("points: %d", player.points);
}

void receivePlayerInput() {
    char inputChar = getch();

    switch (inputChar) {
    case 'w': {
        if (player.playerLocationY - 1 != -1) {
            movePlayer(player.playerLocationY - 1, player.playerLocationX);
        }
        break;
    }
    case 's': {
        if (player.playerLocationY + 1 != 10) {
            movePlayer(player.playerLocationY + 1, player.playerLocationX);
        }
        break;
    }
    case 'a': {
        if (player.playerLocationX - 1 != -1) {
            movePlayer(player.playerLocationY, player.playerLocationX - 1);
        }
        break;
    }
    case 'd': {
        if (player.playerLocationX + 1 != 10) {
            movePlayer(player.playerLocationY, player.playerLocationX + 1);
        }
        break;
    }
    }
}

void printResultScreen() {
    printw("=== GAME OVER ===\n");
    printw("number of moves: %d\n", player.numberOfMoves);
    printw("you got %d points\n", player.points);
}

int main()
{
    initscr();
    cbreak();
    noecho();

    setUpMaze();

    while (!isGameOver()) {
        printMaze();
        receivePlayerInput();
        clear();
    }

    clear();

    while (isGameOver()) {
        refresh();
        printResultScreen();
        char inputChar = getch();

        if (inputChar == 'q') {
            break;
        }
    }

    return 0;
}