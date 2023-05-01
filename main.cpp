#include <iostream>
#include <ncurses.h>

const int NUM_ROWS = 10;
const int NUM_COLUMNS = 10;

char maze[NUM_ROWS][NUM_COLUMNS] = {
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

const int playerStartY = 5;
const int playerStartX = 5;
const int goalLocationX = 2;
const int goalLocationY = 2;
const char playerIcon = '@';
const char goalIcon = '%';
const char point = '*';
int playerLocationY = playerStartY;
int playerLocationX = playerStartX;
int numberOfMoves = 0;
int points = 0;

bool isGameOver() {
    return playerLocationX == goalLocationX && playerLocationY == goalLocationY;
}

void movePlayer(int y, int x) {
    if (maze[y][x] == '*') points += 1;
    if (maze[y][x] != '#') {
        numberOfMoves += 1;
        maze[playerLocationY][playerLocationX] = '.';
        maze[y][x] = playerIcon;
        playerLocationY = y;
        playerLocationX = x;
    }
}

void setUpMaze() {
    maze[playerStartY][playerStartX] = playerIcon;
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
    printw("% = goal\n");
    printw("points: %d", points);

    refresh();
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

void printResultScreen() {
    std::cout << "=== GAME OVER ===" << "\n";
    std::cout << "number of moves: " << numberOfMoves << "\n";
    std::cout << "you got " << points << " points" << "\n";
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

    printResultScreen();
    clear();

    return 0;
}