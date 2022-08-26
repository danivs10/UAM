package src;
/**
 * Enumeration class for the possible colors
 * @author Pablo Sancho & Daniel Varela
 */
public enum Color {
    RED("[#red]"), YELLOW("[#yellow]"), BLUE("[#blue]"), BLACK("[#black]");

    private final String text;

    /**
     * Constructor for an object of class Color
     * @param text
     */
    Color(final String text) {
        this.text = text;
    }

    /**
     * Passsing the color to a string
     */
    @Override
    public String toString() {
        return text;
    }
}
