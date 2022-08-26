package src.list;

import java.util.function.*;

/**
 * Class that represents a When letter.
 * 
 * @author Pablo Sancho & Daniel Varela
 * @version 1.0
 */
public class When<T> extends Letter<T> {
    private Predicate<T> p;

    /**
     * Constructor for the When class.
     * 
     * @param letter String to be printed.
     * @param p      Predicate to be applied to the object.
     */
    public When(Predicate<T> p, String string) {
        super(string, null);
        this.p = p;
    }

    /**
     * Method to emit the letter.
     * 
     * @param o Object to be printed.
     * @return String with the letter.
     */
    @Override
    public String emit(T o) {
        String output = "";
        if (p.test(o)) {
            output += super.getLetter();
        }
        return output + "\n";
    }

}
