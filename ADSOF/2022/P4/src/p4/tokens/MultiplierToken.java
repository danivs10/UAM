package p4.tokens;

import p4.game.*;

public class MultiplierToken extends Token {
    /**
     * Constructor for MultiplierToken
     * @param p the player that owns the token
     */
    public MultiplierToken(Player p) {
        super(p, true, 3);
    }

    /*
     * Converts the token to a string
     * @return the string representation of the token
     */
    @Override
    public String toString() {
        return "M" + super.toString();
    }
}
