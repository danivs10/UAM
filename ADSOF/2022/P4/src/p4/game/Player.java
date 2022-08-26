package p4.game;

import java.util.ArrayList;

import p4.interfaces.*;

import java.util.*;

public class Player {
    private static int playerNumber=1;
    private int id;
    private List<ICell> cells= new ArrayList<>();
    double score = 0;
    ICell lastCell = null;

    /**
     * Constructor for Player
     */
    public Player(){
        id=playerNumber;
        playerNumber++;
        if(playerNumber>2){
            /*Throw an exception */
            return;
        }

    }

    /**
     * Gets the id of the player
     * @return the id of the player
     */
    public int getPlayerId (){
        return this.id;
    }


    /**
     * Gets the score of the player
     * @return the score of the player
     */
    public double getScore(){
        return this.score;
    }

    /**
     * Sets the score of the player
     * @param s the score to be set
     */
    public void setScore(double s){
        this.score=s;
    }

    /**
     * Sets the last cell of the player
     * @param cell the cell to be set
     */
    public void setLastCell(ICell cell){
        this.lastCell=cell;
        this.cells.add(cell);
    }

    /**
     * Gets the last cell of the player
     * @return the last cell of the player
     */
    public ICell getLastCell(){
        return this.lastCell;
    }

    public void lostCell(ICell cell){
        this.cells.remove(cell);
    }

    public boolean hasCell(ICell cell){
        return this.cells.contains(cell);
    }
}

