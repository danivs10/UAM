package p4.exception;

public class InvalidGame extends Exception { 
    /**
     * Constructor for InvalidGame
     * @param message the message to display
     */
    public InvalidGame(String errorMessage) {
        super(errorMessage);
    }
}
