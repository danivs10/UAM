package p4.game;

import java.util.*;
import p4.exception.*;
import p4.tokens.*;
import p4.interfaces.*;

public class BoardGame implements IBoard {
    private int size;
    private int rows;
    private int columns;
    private Player player1;
    private Player player2;
    private ArrayList<ArrayList<Cell>> boardx = new ArrayList<>();
    private List<ICell> enhancers = new ArrayList<>();
    private List<ICell> walls = new ArrayList<>();
    private int nWalls = 1;

    /**
     * Constructor of the class BoardGame
     * 
     * @param size
     *                   Size of the board
     * @param player1
     *                   Player 1
     * @param player2
     *                   Player 2
     * @param wallTokens
     *                   Number of wall tokens
     * @throws InvalidGame
     *                     If the board is invalid
     */
    public BoardGame(int s, Player p1, Player p2) {
        this.setupBoard(s, p1, p2, this.nWalls);
    }

    /**
     * Constructor of the class BoardGame
     * 
     * @param size
     *                   Size of the board
     * @param player1
     *                   Player 1
     * @param player2
     *                   Player 2
     * @param wallTokens
     *                   Number of wall tokens
     * @throws InvalidGame
     *                     If the board is invalid
     */
    public BoardGame(int s, Player p1, Player p2, int wallTokens) {
        this.nWalls = wallTokens;
        this.setupBoard(s, p1, p2, this.nWalls);
    }

    /*
     * setup of the initial board
     * 
     * @param size
     * Size of the board
     * 
     * @param player1
     * Player 1
     * 
     * @param player2
     * Player 2
     * 
     * @param wallTokens
     * Number of wall tokens
     * 
     * @throws InvalidGame
     * If the board is invalid
     */
    public void setupBoard(int s, Player p1, Player p2, int wallTokens) {

        this.size = s;
        this.rows = s;
        this.columns = s;
        this.player1 = p1;
        this.player2 = p2;

        ArrayList<Cell> boardy = null;

        for (int i = 0; i < s; i++) {

            boardy = new ArrayList<>();
            for (int j = 0; j < s; j++) {
                boardy.add(new Cell(i, j));

            }
            this.boardx.add(boardy);
        }

        try {
            this.probabilityAddToken(0, 0, this.player1, true);
            this.probabilityAddToken(size - 1, size - 1, this.player2, true);
            this.createEnhancers();
            this.createWalls(wallTokens);

        } catch (ForbiddenToken e) {
            System.out.println(e);
        }
    }

    /**
     * Adds the token from a player to the board
     * 
     * @param row    Row of the cell
     * @param column Column of the cell
     * @param token  Token to be added
     * @throws ForbiddenToken If the token is not allowed
     */
    public void probabilityAddToken(int row, int column, Player p, boolean normal) throws ForbiddenToken {
        double random = 0;
        random = Math.random();
        double score = 1;
        boolean notOwned=true;
        ICell auxc = null;
        IToken t=null;
        /* if the cell is neighbour to the lastcell of the player */
        if ( normal==false ){
            if (this.getCell(row, column).isNeighbor(p.getLastCell()) == false) {
                throw new ForbiddenToken("The cell is not neighbour to the last cell of the player");
            }
        }
        /* if the cell is not empty */
        if (this.getCell(row, column).getToken() == null || this.getCell(row, column).getToken().canBeOverwritten()) {
            /* check if cell position is in the enhancers */
            for (ICell c : this.enhancers) {

                if (c.getRow() == row && c.getColumn() == column) {
                    auxc = c;
                    break;
                }
            }

            if (auxc != null) {
                applyEnhancer(auxc, p);
                createEnhancers();
                return;
            }

            if (this.getCell(row, column).getToken() != null){
                if (this.player1==p){
                    
                    if (this.player2.hasCell(this.getCell(row, column))){
                        System.out.println(this.getCell(row, column).getToken()+ " AAAAAAA ");
                        /** aqui substraer los puntos necesarios de esa cell del player 2 */
                        if (this.getCell(row, column).getToken().toString().equals("M2 ")){
                            this.player2.setScore(this.player2.getScore()-3);
                        }
                        else if (this.getCell(row, column).getToken().toString().equals("N2 ")){
                            
                            System.out.println(" PONCHO ");
                            this.player2.setScore(this.player2.getScore()-1);
                        }
                    }
                    else{
                        notOwned=false;
                    }
                }
                else {
                    if (this.player1.hasCell(this.getCell(row, column))){
                        /** aqui substraer los puntos necesarios de esa cell del player 1 */
                        System.out.println(this.getCell(row, column).getToken()+ " AAAAAAA ");
                        if (this.getCell(row, column).getToken().toString().equals("M1 ")){
                            this.player1.setScore(this.player1.getScore()-3);
                        }
                        else if (this.getCell(row, column).getToken().toString().equals("N1 ")){
                            System.out.println(" RONCHO ");
                            this.player1.setScore(this.player1.getScore()-1);
                        }
                    }
                    else{
                        notOwned=false;
                    }
                }
            }

            if (random < 0.7 || normal==true) {
                t=new NormalToken(p);
            } else if (random < 0.9) {
                t=new FixedToken(p);
            } else {
                t=new MultiplierToken(p);
                score = 3;
            }
            this.addToken(row, column, t);
            p.setLastCell(this.getCell(row, column));
            if (notOwned){
                p.setScore(p.getScore() + score);
            }

        }
        else{
            throw new ForbiddenToken(
                    "Error. Token " + t.toString() + "can not be placed in position " + row + "," + column
                            + " because: the cell contains a token that cannot be overwritten\n");
        }

    }





    /*
     * Gets a cell given a row and column
     * 
     * @param row Row of the cell
     * 
     * @param column Column of the cell
     * 
     * @return Cell
     */
    @Override
    public ICell getCell(int row, int column) {
        List<Cell> rows;

        for (int i = 0; i < this.rows; i++) {
            rows = this.boardx.get(i);
            for (Cell auxCell : rows) {
                if (auxCell.getRow() == (row) && auxCell.getColumn() == (column))
                    return auxCell;
            }

        }

        return null;
    }

    /*
     * Gets the amount of rows
     * 
     * @return int
     */
    @Override
    public int getRows() {
        return this.rows;
    }

    /*
     * Gets the amount of columns
     * 
     * @return int
     */
    @Override
    public int getColumns() {
        return this.columns;
    }

    /*
     * Adds a given token to the board
     * 
     * @param row Row of the cell
     * 
     * @param column Column of the cell
     * 
     * @param token Token to be added
     * 
     * @throws ForbiddenToken If the token is not allowed
     */
    @Override
    public void addToken(int row, int column, IToken f) throws ForbiddenToken {
        ICell auxCell;

        auxCell = this.getCell(row, column);
        if (auxCell != null) {
            if (auxCell.getToken() == null || auxCell.getToken().canBeOverwritten()) {
                auxCell.setToken(f);
            }
            else {
                throw new ForbiddenToken(
                        "Error. Token " + f.toString() + "can not be placed in position " + row + "," + column
                                + " because: the cell contains a token that cannot be overwritten\n");
            }
        }

    }

    /*
     * This method gets the neighbours of a given position
     * 
     * @param row
     * 
     * @param column
     * 
     * @return a list of neighbours
     */
    @Override
    public List<ICell> getNeighbors(int row, int column) {
        List<ICell> neighbours = new ArrayList<>();
        int i, j = 0;

        for (i = row - 1; i <= row + 1; i++) {
            for (j = column - 1; j <= column + 1; j++) {
                if (i < 0 || i > size-1 || j < 0 || j > size-1)
                    continue;

                System.out.println("cell " + row + "," + column + " its adyacent its" + this.getCell(i, j));
                //if(this.getCell(i, j),equals(null)
                neighbours.add(this.getCell(i, j));
            }
        }

        return neighbours;
    }

    /*
     * This method gets the symetric cell of a given cell
     * 
     * @param cell
     * 
     * @return the symetric cell
     */
    @Override
    public ICell getSymmetric(ICell c) {
        return this.getCell(this.size - 1 - c.getRow(), this.size - 1 - c.getColumn());
    }

    /*
     * This method prints the current state of the board
     * 
     * @return a string with the state of the board
     */
    @Override
    public String toString() {

        String output = "";
        for (int i = 0; i < this.size; i++) {
            for (int j = 0; j < this.size; j++) {
                output += (this.boardx.get(i)).get(j).toString();
            }
            output += "\n";
        }
        return output;
    }

    /**
     * This method creates the enhancers of the board
     * 
     * @throws ForbiddenToken
     */
    public void createEnhancers() throws ForbiddenToken {
        createNewPositions(-1);
    }

    /**
     * This method creates the walls of the board
     * 
     * @param wallTokens
     * @throws ForbiddenToken
     */
    public void createWalls(int number) throws ForbiddenToken {
        createNewPositions(number);
    }

    /**
     * This method creates the new positions of the enhancers and or walls on the
     * board
     * 
     * @param number if -1 creates the enhancers, if not creates the walls
     * @throws ForbiddenToken
     */
    public void createNewPositions(int t) throws ForbiddenToken {
        boolean correctPos = false;
        int i = 0;
        if (t == -1) {
            for (ICell c : this.enhancers) {
                c.setToken(null);
            }
            this.enhancers.clear();

        } else if (t > 0) {
            for (ICell c : this.walls) {
                c.setToken(null);
            }
            this.walls.clear();
        } else {
            return;
        }
        while (correctPos == false) {
            int x = (int) Math.floor(Math.random() * (this.size));
            int y = (int) Math.floor(Math.random() * (this.size));
            if (this.getCell(x, y).getToken() == null && this.getSymmetric(this.getCell(x, y)).getToken() == null) {
                if (t == -1) {
                    /* empty the tokens in the enhancer cells */
                    this.enhancers.add(this.getCell(x, y));
                    this.enhancers.add(this.getSymmetric(this.getCell(x, y)));
                    this.addToken(x, y, new EnhancerToken());
                    this.addToken(size - 1 - x, size - 1 - y, new EnhancerToken());
                    correctPos = true;
                } else {
                    this.walls.add(this.getCell(x, y));
                    this.walls.add(this.getSymmetric(this.getCell(x, y)));
                    this.addToken(x, y, new WallToken());
                    this.addToken(size - 1 - x, size - 1 - y, new WallToken());
                    if (i < t - 1) {
                        i++;
                    } else {
                        correctPos = true;
                    }
                }
            }
        }
    }

    /**
     * This method creates both the enhancers and walls of the board
     * 
     * @return a list of enhancers
     */
    public void newTurnPositions() throws ForbiddenToken {
        createNewPositions(this.nWalls);
        createNewPositions(-1);
    }

    /**
     * This method applies the effects of the enhancer
     * 
     * @param c cell where the enhancer was applied
     * @param p player that has obtained the enhancer
     * @throws ForbiddenToken
     */

    public void applyEnhancer(ICell c, Player p) throws ForbiddenToken {
        /* 33% probablility of three different cases */
        double random = 0;
        random = Math.random();

        for (ICell ce : this.enhancers) {
            ce.setToken(null);
        }
        this.enhancers.clear();

        if (random < 0.33) {
            System.out.println("area boost");
            /* insert normal tokens in all the neighbour cells to c */
            this.probabilityAddToken(c.getRow(), c.getColumn(), p, true);
            for (ICell auxCell : this.getNeighbors(c.getRow(), c.getColumn())) {
                if (auxCell.getToken() == null || auxCell.getToken().canBeOverwritten()) {
                    this.probabilityAddToken(auxCell.getRow(), auxCell.getColumn(), p, true);
                }
            }
        } else if (random < 0.66) {
            System.out.println("row boost");
            /* insert normal tokens in all the row of c */
            for (int i = 0; i < this.size; i++) {
                if (this.getCell(c.getRow(), i).getToken() == null
                        || this.getCell(c.getRow(), i).getToken().canBeOverwritten()) {
                    this.getCell(c.getRow(), i).setToken(new NormalToken(p));
                    this.probabilityAddToken(c.getRow(), i, p, true);
                }
            }
        } else {
            /* insert normal tokens in all the column of c */
            System.out.println("column boost");
            for (int i = 0; i < this.size; i++) {
                if (this.getCell(i, c.getColumn()).getToken() == null
                        || this.getCell(i, c.getColumn()).getToken().canBeOverwritten()) {
                    this.probabilityAddToken(i, c.getColumn(), p, true);
                }
            }
        }
    }
}
