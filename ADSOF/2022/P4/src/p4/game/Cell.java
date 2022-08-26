package p4.game;

import p4.interfaces.*;

public class Cell implements ICell {

    private int row;
    private int column;
    private IToken token = null;

    /**
     * Constructor
     * @param row
     * @param column
     */
    public Cell(int r, int c) {
        this.row = r;
        this.column = c;
    }

    /**
     * Getter
     * @return row
     */
    @Override
    public int getRow() {
        return this.row;
    }

    /**
     * Getter
     * @return column
     */
    @Override
    public int getColumn() {
        return this.column;
    }

    /**
     * Getter
     * @return token
     */
    @Override
    public IToken getToken() {
        return this.token;
    }

    /**
     * Setter
     * @param token
     */
    @Override
    public void setToken(IToken f) {
        this.token = f;
    }

    /* check if the given cell is neighbour to this one 
    * @param c the cell to check
    */
    @Override
    public boolean isNeighbor(ICell c) {
        if (Math.abs(c.getRow() - this.getRow())==1 || c.getRow()==this.getRow()) {
            if (Math.abs(c.getColumn() - this.getColumn())==1 || c.getColumn()==this.getColumn()) {
                return true;
            }
        }
        return false;
    }

    /* Converts the cell to a string
    * @return the string representation of the cell
    */
    @Override
    public String toString() {
        if (this.token == null) {
            return "-- ";
        } else {
            return this.token.toString();
        }
    }

}
