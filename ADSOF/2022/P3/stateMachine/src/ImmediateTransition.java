package src;

/**
 * Class that contains an immediate Transition
 * @author Pablo Sancho & Daniel Varela
 */
public class ImmediateTransition extends Transition{
    private Color color;
    
    /**
     * Constructor for the class
     * @param source source state of the transition
     * @param destination destination state of the transition
     * @param c color for the transition
     */
    public ImmediateTransition(State source, State destination, Color c) {
        super(source, destination);
        this.color=c;
    }

    /**
     * Method that returns the state in the UML notation to generate plantuml
     */    
    @Override
    public String getUML(){
        return super.getUML()+this.color+"->"+this.destination.getName()+"\n";
    }

    /**
     * Passsing the class to a string
     */
    @Override
    public String toString(){
        return ("====>"+super.destination.getName());
    }
}