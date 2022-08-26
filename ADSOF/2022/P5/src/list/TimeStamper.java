package src.list;

import java.time.LocalDate;

/**
 * Class that represents TimeStamper Option.
 * @author Pablo Sancho & Daniel Varela
 * @version 1.0
 */
public class TimeStamper<T> implements IOption<T> {
    private String message;
    private String timeStamp;

    /**
     * Method that applies the TimeStamper class.
     * @param message String with the message to be printed.
     * @param o Object from which the message is from.
     * @return String with the message modified.
     */
    @Override
    public String apply(Object o, String message) {
        String output = "";
        this.timeStamp = LocalDate.now().toString();
        this.message = message;
        output += this.timeStamp + "\n" + this.message;
        return output;
    }

    
}
