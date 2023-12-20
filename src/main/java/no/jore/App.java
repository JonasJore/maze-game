package no.jore;

import java.io.IOException;

public class App {
  public static void main(String[] args) throws IOException {
    System.out.println("Hello World!");
    MazeGame instance = new MazeGame();

    instance.gameLoop();
  }
}
