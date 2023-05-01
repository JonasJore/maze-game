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
const int playerStartY = 5;
const int playerStartX = 5;
int playerLocationY = playerStartY;
int playerLocationX = playerStartX;
const int goalLocationX = 2;
const int goalLocationY = 2;
const char goalIcon = '%';
int numberOfMoves = 0;

bool isGameOver() {
    return (playerLocationX == goalLocationX && playerLocationY == goalLocationY);
}

void movePlayer(int y, int x) {
    numberOfMoves += 1;
    maze[playerLocationY][playerLocationX] = '.';
    maze[y][x] = playerIcon;
    playerLocationY = y;
    playerLocationX = x;
}

void receivePlayerInput() {
    char inputChar = getch();

    switch (inputChar) {
    case 'w': {
        if (playerLocationY - 1 != -1) {
            movePlayer(playerLocationY - 1, playerLocationX);
        }
        break;
    }
    case 's': {
        if (playerLocationY + 1 != 10) {
            movePlayer(playerLocationY + 1, playerLocationX);
        }
        break;
    }
    case 'a': {
        if (playerLocationX - 1 != -1) {
            movePlayer(playerLocationY, playerLocationX - 1);
        }
        break;
    }
    case 'd': {
        if (playerLocationX + 1 != 10) {
            movePlayer(playerLocationY, playerLocationX + 1);
        }
        break;
    }
    }
}

void printMaze() {
    maze[goalLocationY][goalLocationX] = goalIcon;
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            printw("%c", maze[y][x]);
        }
        printw("\n");
    }
    refresh();
}

void printResultScreen() {
    std::cout << "=== GAME OVER ===" << "\n";
    std::cout << "number of moves: " << numberOfMoves << "\n";
}

int main()
{
    initscr();
    cbreak();
    noecho();
    maze[playerStartY][playerStartX] = playerIcon;
    while (!isGameOver()) {
        printMaze();
        receivePlayerInput();
        clear();
    }
    printResultScreen();
    clear();

    return 0;
}