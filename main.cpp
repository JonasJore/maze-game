#include <iostream>
#include <ncurses.h>

// const int ROWS = 10;
// const int COLS = 10;

char maze[10][10] = {
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},    // @ = player
    {'.','.','.','.','.','.','.','.','.','.'},    // % = goal
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
};

const char playerIcon = '@';
const int playerStartX = 5;
const int playerStartY = 5;
int playerLocationX = playerStartX;
int playerLocationY = playerStartY;
const int goalLocationX = 8;
const int goalLocationY = 8;
const char goalIcon = '%';

bool isGameOver() {
    if (playerLocationX == goalLocationX && playerLocationY == goalLocationY) {
        return true;
    }
    else false;
}

void movePlayer(int x, int y) {
    maze[playerLocationX][playerLocationY] = '2';
    maze[x][y] = playerIcon;
    playerLocationX = x;
    playerLocationY = y;
}

void receivePlayerInput() {
    char inputChar = getch();
    std::cout << inputChar << "\n";
    switch (inputChar) {
    case 'w': {
        movePlayer(playerLocationX - 1, playerLocationY);
    }
    case 's': {
        movePlayer(playerLocationX + 1, playerLocationY);
    }
    case 'a': {
        movePlayer(playerLocationX, playerLocationY - 1);
    }
    case 'd': {
        movePlayer(playerLocationX, playerLocationY + 1);
    }
    }
}

void printMaze() {
    maze[playerStartX][playerStartY] = playerIcon;
    maze[goalLocationX][goalLocationY] = goalIcon;

    for (int x = 0; x <= 10; x++) {
        for (int y = 0; y <= 10; y++) {
            printw("%c", maze[x][y]);
        }
        printw("\n");
    }
    refresh();
}

int main()
{
    initscr();
    cbreak();
    noecho();

    while (!isGameOver()) {
        printMaze();
        receivePlayerInput();
        clear();
    }

    clear();
    std::cout << "GAME OVER" << "\n";

    return 0;
}