package p4.tokens;

import p4.game.*;

public class FixedToken extends Token {
    /**
     * Constructor for FixedToken
     */
    public FixedToken(Player p) {
        super(p, false, 1);
    }

    /*
     * Converts the token to a string
     * 
     * @return the string representation of the token
     */
    @Override
    public String toString() {
        return "F" + super.toString();
    }
}
