package src.list;

/**
 * Interface for the Options on the letters.
 * @author Pablo Sancho & Daniel Varela
 * @version 1.0
 */
@FunctionalInterface
public interface IOption<T> {
    public String apply(T o, String message);
}
