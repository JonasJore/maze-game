package no.jore;

public class MazeGame {
  MazeGame() {
  }

  // TODO: implement multiple levels later
  // TODO: fixed size for arrays
  char[][] maze = {
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '#', '.', '.', '.', '.', '.', '*'},
      {'.', '.', '.', '#', '.', '.', '.', '.', '.', '.'}, // @ = player
      {'.', '.', '.', '#', '.', '.', '.', '.', '.', '.'}, // % = goal
      {'.', '#', '.', '.', '.', '.', '.', '.', '.', '*'}, // * = point
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
        && this.player.getPlayerY() == this.goalLocationY;
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

  private void setUpMaze() {
    maze[this.player.getPlayerY()][this.player.getPlayerX()] = this.player.getPlayerIcon();
    maze[this.goalLocationX][this.goalLocationY] = this.goalIcon;
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

  public void gameLoop() {
    this.setUpMaze();
    this.printMaze();


    while (!isGameOver()) {
      printMaze();
    }

  }

}
