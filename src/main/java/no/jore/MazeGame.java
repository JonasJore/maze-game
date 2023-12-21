package no.jore;

import java.util.Random;
import java.util.Scanner;

public class MazeGame {
  private final Scanner input;
  private boolean isGamePaused;

  MazeGame() {
    input = new Scanner(System.in);
    isGamePaused = false;
  }

  // TODO: implement multiple levels later
  // TODO: fixed size for arrays
  char[][] maze = {
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '#', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '#', '.', '.', '.', '.', '.', '.'}, // @ = player
      {'.', '.', '.', '#', '.', '.', '.', '.', '.', '.'}, // % = goal
      {'.', '#', '.', '.', '.', '.', '.', '.', '.', '.'}, // * = point
      {'.', '#', '.', '.', '.', '.', '.', '.', '.', '.'}, // # = barrier
      {'.', '#', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '#', '.', '.', '.', '.', '.', '.', '.', '.'},
  };

  final int goalLocationX = 2;
  final int goalLocationY = 2;
  final char goalIcon = '%';
  final char pointIcon = '*';
  Player player = new Player();

  private boolean isGameOver() {
    return this.player.getPlayerX() == this.goalLocationX
        && this.player.getPlayerY() == this.goalLocationY
        || isGamePaused;
  }

  private void setIsGamePaused(boolean b) { // TODO: better name for b
    this.isGamePaused = b;
  }

  void printMaze() {
    for (int y = 0; y < 10; y++) {
      for (int x = 0; x < 10; x++) {
        System.out.print(maze[y][x]);
      }
      System.out.println();
    }
    System.out.println("Points: " + this.player.getPoints());
    System.out.println("Moves: " + this.player.getNumberOfMoves());
  }

  // TODO: implement try-again mechanism until random position is a '.'
  // now it just skips placing points if location is not '.'
  private void spawnPoints(int points) {
    Random rand = new Random();
    for (int i = 0; i < points; i++) {
      int randomXPosition = rand.nextInt(maze.length);
      int randomYPosition = rand.nextInt(maze[0].length);
      if (maze[randomXPosition][randomYPosition] == '.') {
        maze[randomXPosition][randomYPosition] = this.pointIcon;
      }
    }
  }

  private void setUpMaze() {
    maze[this.player.getPlayerY()][this.player.getPlayerX()] = this.player.getPlayerIcon();
    maze[this.goalLocationX][this.goalLocationY] = this.goalIcon;
    spawnPoints(3);
  }

  private void movePlayer(int x, int y) {
    if (maze[y][x] == '*') this.player.setPoints(this.player.getPoints() + 1);
    if (maze[y][x] != '#') {
      this.player.setNumberOfMoves(this.player.getNumberOfMoves() + 1);
      maze[this.player.playerY][this.player.playerX] = '.';
      maze[y][x] = this.player.playerIcon;
      this.player.setPlayerY(y);
      this.player.setPlayerX(x);
    }
  }

  private void receivePlayerInput() {
    System.out.println("INPUT:");
    char inputChar = input.nextLine().charAt(0);
    switch (inputChar) {
      case 'w': {
        if (this.player.getPlayerY() - 1 != -1)
          movePlayer(this.player.getPlayerX(), this.player.getPlayerY() - 1);
        break;
      }
      case 's': {
        if (this.player.getPlayerY() + 1 != 10)
          movePlayer(this.player.getPlayerX(), this.player.getPlayerY() + 1);
        break;
      }
      case 'a': {
        if (this.player.getPlayerX() - 1 != -1)
          movePlayer(this.player.getPlayerX() - 1, this.player.getPlayerY());
        break;
      }
      case 'd': {
        if (this.player.getPlayerX() + 1 != 10)
          movePlayer(this.player.getPlayerX() + 1, this.player.getPlayerY());
        break;
      }
      case 'p': {
        setIsGamePaused(true);
        displayPauseScreen();
        break;
      }
      default: {
        System.out.println("not valid input, press `p` to pause the game and get info on how to play");
      }
    }
  }

  void displayPauseScreen() {
    System.out.println("===============================================");
    System.out.println("Welcome to the maze game");
    System.out.println("Playing is rather simple:");
    System.out.println("You control the `@` in the maze");
    System.out.println("Controls:");
    System.out.println("\t- Press `w` to go up");
    System.out.println("\t- Press `s` to go down");
    System.out.println("\t- Press `a` to go left");
    System.out.println("\t- Press `d` to go right\n");
    System.out.println("`.` means a free spot which is safe to go to");
    System.out.println("`#` are barriers you cannot go through");
    System.out.println("`*` are points you must collect in order to win");
    System.out.println("===============================================");
    input.nextLine();

    setIsGamePaused(false);
  }

  public void gameLoop() {
    this.setUpMaze();
    this.printMaze();

    while (!isGameOver()) {
      receivePlayerInput();

      printMaze();
    }
  }

}
