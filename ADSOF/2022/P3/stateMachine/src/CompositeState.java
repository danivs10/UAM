package src;

import java.util.ArrayList;
import java.util.*;

/**
 * Class that contains a Composite state
 * @author Pablo Sancho & Daniel Varela
 */
public class CompositeState extends State{
    private State initialState=null;
    private List<State> states= new ArrayList<>();
        
    /**
     * Constructor for a composite state
     * @param name name of the state
     */
    CompositeState(String name) {
        super(name);
    }

    /**
     * Constructor for a composite state that has a parent state
     * @param name name of the state
     * @param parent parent of the state
     */
    CompositeState(String name, CompositeState parent) {
        super(name, parent);
    }

    /**
     * Function that creates a simple state with a description inside the composite state and returns it
     * @param name name of the new state
     * @param description description of the new state
     * @return the created simple state
     */
    public SimpleState createState(String name, String description) {
        SimpleState auxState = null;
        auxState = this.createState(name);
        if (auxState != null) {
            auxState.setDescription(description);
        }
        return auxState;
    }

    /**
     * Function that creates a simple state inside the composite state and returns it
     * @param name name of the new state
     * @return the created simple state
     */
    public SimpleState createState(String name) {
        SimpleState auxState = null;
        if (checker(name)) {
            auxState = new SimpleState(name, this);
            this.states.add(auxState);
            return auxState;
        }
        return null;

    }


    /**
     * Function that creates a composite state inside the composite state and returns it
     * @param name name of the new state
     * @return the created simple state
     */
    public CompositeState createCompositeState(String name) {
        CompositeState auxState = null;
        if (checker(name)) {
            auxState = new CompositeState(name, this);
            this.states.add(auxState);
            return auxState;
        }
        return null;

    }
    
    /**
     * Amethod that checks whether the name of a new state is possible within the constraints of state names
     * @param name name of the new state
     * @return true or false depending on if the new stste can be called like that or not
     */
    public boolean checker(String name) {
        return (name != null && name.matches("^[a-zA-Z0-9]*$") && stateChecker(name));
    }


    /**
     * Checks if a state with that name already exists in this composite state 
     * @param name name of the state
     * @return true or false depending on if name already exists or not (if it exists False, if it does not True)
     */
    public boolean stateChecker(String name) {

        for (State s : this.states) {
            if (s.getName().equals(name)) {
                return false;
            }
        }
        return true;
    }
    /**
     * Method that returns the initial node recursively
     */
    @Override
    public SimpleState getInitial(){
        if (this.initialState!=null){
            return this.initialState.getInitial();
        }
        return null;
    }

    
    /**
     * Setter for the initial state
     * @param s name of the state wanted to be initial
     */
    public void setInitial(String s){
        for(State state : this.states){
            if(state.getName().equals(s)){
                this.initialState=state.getInitial();
            }
        }
    }

    /**
     * Checker that returns wether the source and destination exist qwithin this composite state level
     * @param source source state name
     * @param destination destination stste name
     * @return true if they both exist false otherwise
     */
    public Boolean connectionCheck(String source, String destination) {
        Boolean sourcecheck = false;
        Boolean destinationcheck = false;
        for (State s : this.states) {
            if (s.getName().equals(source)) {
                sourcecheck = true;
            }
            if (s.getName().equals(destination)) {
                destinationcheck = true;
            }
        }
        return sourcecheck && destinationcheck;
    }

    /**
     * Method that returns a state in this level given a name if it exists
     * @param name name of the state being searched
     * @return the state if found, null otherwise
     */
    public State getStateByName(String name) {
        for (State s : this.states) {
            if (s.getName().equals(name)) {
                return s;
            }
        }
        return null;
    }


    /**
     * Method that connects two nodes with an immediate transition
     * @param source name of the source string 
     * @param destination name of the destination string 
     * @param c the color of such transition
     * @return true if the connection was made succesfully, false if not
     */
    public Boolean connect(String source, String destination, Color c) {
        if (!this.connectionCheck(source, destination)) {
            return false;
        }
        
        return this.getStateByName(source).addTransition(getStateByName(destination), c);
    }

    
    /**
     * Method that connects two nodes with an triggered transition
     * @param source name of the source string 
     * @param destination name of the destination string 
     * @param s the method of such transition
     * @return true if the connection was made succesfully, false if not
     */
    public Boolean connect(String source, String destination, String s) {
        if (!this.connectionCheck(source, destination)) {
            return false;
        }
        return this.getStateByName(source).addTransition(getStateByName(destination), s);

    }

    /**
     * Method that returns the state in the UML notation to generate plantuml
     */   
    @Override
    public String getUML(){
        String ret = super.getUML()+"{\n";
        ArrayList<Transition> trans = new ArrayList<>();
        for(State s : this.states){
            ret=ret+"\t"+s.getUML();
            trans.addAll(s.getTransitions());
        }
        if(this.getInitial()!=null){
            ret+="\t[*]-->"+this.getInitial().getName()+"\n";
        }
        for (Transition t : trans){
            ret+="\t"+t.getUML();
        }
        return ret+"}\n";
    }

    /**
     * Passsing the class to a string
     */
    @Override
    public String toString(){
        String ret=super.toString()+"] with states {";
        List<String> auxs = new ArrayList<>();
        for (State s : this.states){
            auxs.add(s.toString());
        }
        ret=ret+String.join(", ", auxs);
        return (ret+"}");
    }


}
