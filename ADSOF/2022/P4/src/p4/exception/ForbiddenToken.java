package p4.exception;
public class ForbiddenToken extends Exception { 
    /**
     * Constructor for ForbiddenToken
     */
    public ForbiddenToken(String errorMessage) {
        super(errorMessage);
    }
}