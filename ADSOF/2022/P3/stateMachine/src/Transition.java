package src;


/**
 * Class that contains an abstract Transition
 * @author Pablo Sancho & Daniel Varela
 */
public abstract class Transition {
    protected State source;
    protected State destination;

    
    /**
     * Constructor for the class
     * @param source source state of the transition
     * @param destination destination state of the transition
     */
    public Transition(State source, State destination) {
        this.source = source;
        this.destination = destination;
    }

    
    /**
     * Method that returns the state in the UML notation to generate plantuml
     */    
    public String getUML(){
        return source.getName()+"-";
    }

    /**
     * Getter for the destination state of the transition
     */
    public State getDestination(){
        return this.destination;
    }

}
