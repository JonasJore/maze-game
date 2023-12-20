package no.jore;

import java.io.IOException;

public class App {
  public static void main(String[] args) throws IOException {
    MazeGame instance = new MazeGame();

    instance.gameLoop();
  }
}
