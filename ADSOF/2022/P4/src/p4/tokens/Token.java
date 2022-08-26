package p4.tokens;

import p4.interfaces.*;
import p4.game.*;

public abstract class Token implements IToken {
    private boolean overwritten;
    private Player owner;
    public int score;

    /**
     * Constructor for Token
     * @param owner the player that owns the token
     * @param o if the token can be overwritten
     * @param score value of the token
     */
    public Token(Player owner, boolean o, int score) {
        this.owner = owner;
        this.overwritten = o;
        this.score=score;
    }

    /**
     * Constructor for Token
     * @param o if the token can be overwritten
     */
    public Token(boolean o) {
        this.overwritten = o;
    }

    /**
     * Gets if the token can be overwritten
     * @return if the token can be overwritten
     */
    @Override
    public boolean canBeOverwritten() {
        return this.overwritten;
    }

    /**
     * Converts the token to a string
     * @return the string representation of the token
     */
    @Override
    public String toString() {
        return Integer.toString(this.owner.getPlayerId()) + " ";
    }

    /**
     * Gets the player that owns the token
     * @return the player that owns the token
     */
    public Player getOwner() {
        return owner;
    }

    /**
     * Gets the score of the token
     * @return the score of the token
     */
    public int getScore() {
        return score;
    }
}
