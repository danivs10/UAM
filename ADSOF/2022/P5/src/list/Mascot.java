package src.list;

/**
 * Class for the Mascot.
 * @author Pablo Sancho & Daniel Varela
 * @version 1.0
 */
public class Mascot {
    private String name;
    private String type;

    /**
     * Constructor for the Mascot class.
     * @param name String with the name of the mascot.
     * @param type String with the type of the mascot.
     */
    public Mascot(String name, String type) {
        this.name = name;
        this.type = type;
    }

    /**
     * Method to get the name of the mascot.
     * @return String with the name of the mascot.
     */
    public String getMascotName() {
        return name;
    }

    /**
     * Method to get the type of the mascot.
     * @return String with the type of the mascot.
     */
    public String getMascotType() {
        return type;
    }
}
