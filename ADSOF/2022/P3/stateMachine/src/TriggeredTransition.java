package src;


/**
 * Class that contains a triggered transition
 * @author Pablo Sancho & Daniel Varela
 */
public class TriggeredTransition extends Transition{
    private String event;

    
    /**
     * Constructor for the class
     * @param source source state of the transition
     * @param destination destination state of the transition
     * @param event event for the transition
     */
    public TriggeredTransition(State source, State destination, String event) {
        super(source, destination);
        this.event=event;
    }

    /**
     * Getter for the event string
     * @return the event string
     */
    public String getEvent(){
        return this.event;
    }

    
    /**
     * Method that returns the state in the UML notation to generate plantuml
     */    
    @Override
    public String getUML(){
        return super.getUML()+"->"+this.destination.getName()+": "+this.getEvent()+"\n";
    }

    /**
     * Passsing the class to a string
     */
    @Override
    public String toString(){
        return ("--"+this.event+"-->"+super.destination.getName());
    }
}