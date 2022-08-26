package p4.tokens;


public class WallToken extends Token{
    /**
     * Constructor for WallToken
     */
    public WallToken(){
        super(false);
    }
    
    /*
     * Converts the token to a string
     * @return the string representation of the token
     */
    @Override
    public String toString() {
        return "WA ";
    }
}
