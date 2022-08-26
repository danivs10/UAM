package src.list;

/**
 * Class that represents UpperCaser Option.
 * 
 * @author Pablo Sancho & Daniel Varela
 * @version 1.0
 */
public class UpperCaser<T> implements IOption<T> {
    private String message;

    /**
     * Method that applies the UpperCaser class.
     * 
     * @param message String with the message to be printed.
     * @param o       Object from which the message is from.
     * @return String with the message modified.
     */
    @Override
    public String apply(Object o, String message) {
        this.message = message;
        return this.message.toUpperCase();
    }

}