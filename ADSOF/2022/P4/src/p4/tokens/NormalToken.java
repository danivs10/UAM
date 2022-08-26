package p4.tokens;

import p4.game.*;

public class NormalToken extends Token {
    /**
     * Constructor for NormalToken
     * @param p the player that owns the token
     */
    public NormalToken(Player p) {
        super(p, true, 1);
    }

    /*
     * Converts the token to a string
     * @return the string representation of the token
     */
    @Override
    public String toString() {
        return "N" + super.toString();
    }
}
