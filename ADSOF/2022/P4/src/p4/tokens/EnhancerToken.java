package p4.tokens;


public class EnhancerToken extends Token {

    /**
     * Constructor for EnhancerToken
     */
    public EnhancerToken() {
        super(true);
    }

    /*
    * Converts the token to a string
    * @return the string representation of the token
    */
    @Override
    public String toString() {
        return "EN ";
    }
}
