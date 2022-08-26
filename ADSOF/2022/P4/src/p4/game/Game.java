package p4.game;

import java.io.*;

import p4.exception.*;

public class Game {
    int turns;
    int size;
    int wallTokens;
    BoardGame board;
    Player player1;
    Player player2;

    /**
     * Constructor for Game
     * @param turns the number of turns
     * @param size the size of the board
     * @param wallTokens the number of wall tokens
     * @throws InvalidGame if the game is invalid
     */
    public Game(int turns, int size, int wallTokens) throws InvalidGame {
        this.turns = turns;
        this.size = size;
        this.wallTokens = wallTokens;
        this.player1 = new Player();
        this.player2 = new Player();
        this.board = new BoardGame(size, player1, player2, wallTokens);
        if (wallTokens >= (size - (wallTokens + 1)) || size < 5) {
            throw new InvalidGame(
                    "Invalid board. Number of rows and columns must be 5. Number of wall tokens must not exceed "
                            + (size - wallTokens - 2 + "."));
        }
    }

    /**
     * Play method to play the game
     * @throws InvalidGame if the game is invalid
     */
    public void play() throws InvalidGame {
        int turn = 0, tokenIntroduced = 0;
        String input;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (turn < this.turns) {
            System.out.println("Starting turn " + (turn + 1));
            this.printGame();
            System.out.println("Turn " + (turn + 1));
            while (tokenIntroduced == 0) {
                System.out.println("Player 1 enter the coordinates of the new token");
                try {
                    input = br.readLine();
                    if (input.equals("END")) {
                        break;
                    }
                    String[] coordinates = input.split(",");
                    int row = Integer.parseInt(coordinates[0]);
                    int column = Integer.parseInt(coordinates[1]);
                    this.board.probabilityAddToken(row, column, this.player1, false);
                    tokenIntroduced = 1;
                } catch (NumberFormatException nfe) {
                    System.out.println("Incorrect format");
                }catch (IOException e) {
                    System.out.println("Error reading the values");
                } catch (ForbiddenToken e) {
                    System.out.println(e);
                }
            }
            tokenIntroduced = 0;

            this.printGame();
            System.out.println("Turn " + (turn + 1));
            while (tokenIntroduced == 0) {
                System.out.println("Player 2 enter the coordinates of the new token");
                try {
                    input = br.readLine();
                    if (input.equals("END")) {
                        break;
                    }
                    String[] coordinates = input.split(",");
                    int row = Integer.parseInt(coordinates[0]);
                    int column = Integer.parseInt(coordinates[1]);
                    this.board.probabilityAddToken(row, column, this.player2, false);
                    tokenIntroduced=1;
                } catch (NumberFormatException nfe) {
                    System.out.println("Incorrect format");
                }catch (ForbiddenToken e) {
                    System.out.println(e);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            tokenIntroduced=0;

            this.printGame();
            try {
                this.board.newTurnPositions();
            } catch (ForbiddenToken e) {
                e.printStackTrace();
            }
            turn++;
        }
    }

    /**
     * Prints the game state
     */
    public void printGame() {
        System.out.println(this.board + "\n");
        System.out.println("1: points " + this.player1.getScore() + " last cell: " + this.player1.getLastCell().getRow()
                + "," + this.player1.getLastCell().getColumn());
        System.out.println("2: points " + this.player2.getScore() + " last cell: " + this.player2.getLastCell().getRow()
                + "," + this.player2.getLastCell().getColumn());

    }

}
