package p4.interfaces;

import java.util.List;

import p4.exception.ForbiddenToken;

public interface IBoard {
    /**
     * Gets a cell from the board
     * @param row the row of the cell
     * @param column the column of the cell
     * @return the cell
     */
    public ICell getCell(int row, int column);

    /**
     * Gets the number of rows of the board
     * @return the number of rows
     */
    public int getRows();

    /**
     * Gets the number of columns of the board
     * @return the number of columns
     */
    public int getColumns();

    /**
     * Convert the board to a string
     * @return the string representation of the board
     */
    public String toString();

    /**
     * Adds an specific token to the board
     * @param row the row of the cell
     * @param column the column of the cell
     * @param token the token to add
     * 
     * @throws ForbiddenToken if the token is not allowed
     */
    public void addToken(int row, int column, IToken f) throws ForbiddenToken;

    /**
     * Gets the list of neighbours of a cell
     * @param row the row of the cell
     * @param column the column of the cell
     * @return the list of neighbours
     */
    public List<ICell> getNeighbors(int row, int column);

    /**
     * Gets the symetric cell of a cell
     * @param row the row of the cell
     * @param column the column of the cell
     * @return the symetric cell
     */
    public ICell getSymmetric(ICell c);
}
