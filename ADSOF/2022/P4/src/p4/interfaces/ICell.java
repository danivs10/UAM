package p4.interfaces;

public interface ICell {
    /**
     * Gets the row of the cell
     * @return the row
     */
    public int getRow();
    /**
     * Gets the column of the cell
     * @return the column
     */
    public int getColumn();
    /**
     * Gets the token of the cell
     * @return the token
     */
    public IToken getToken();
    /**
     * Sets the token of the cell
     * @param f the token to set
     */
    public void setToken(IToken f);
    /**
     * Checks if the given cell is neighbour to this one
     * @param c the cell to check
     * @return true if the given cell is neighbour to this one
     */
    public boolean isNeighbor(ICell c);
    }