package no.jore;

public class Player {
  char playerIcon = '@';
  int playerStartX = 5;
  int playerStartY = 5;
  int playerX, playerY, numberOfMoves, points;

  public Player() {
    this.playerX = playerStartX;
    this.playerY = playerStartY;
  }

  public char getPlayerIcon() {
    return playerIcon;
  }

  public int getPlayerX() {
    return playerX;
  }

  public void setPlayerX(int playerX) {
    this.playerX = playerX;
  }

  public int getPlayerY() {
    return playerY;
  }

  public void setPlayerY(int playerY) {
    this.playerY = playerY;
  }

  public int getNumberOfMoves() {
    return numberOfMoves;
  }

  public void setNumberOfMoves(int numberOfMoves) {
    this.numberOfMoves = numberOfMoves;
  }

  public int getPoints() {
    return points;
  }

  public void setPoints(int points) {
    this.points = points;
  }
}