package src;
import java.util.*;

/**
 * Class that contains an abstract state
 * @author Pablo Sancho & Daniel Varela
 */
public abstract class State {
    private String name;
    private CompositeState parent=null;
    private List<TriggeredTransition> ttransitions = new ArrayList<>();
    private ImmediateTransition itransition = null;

    /**
     * Constructor for a state without parent
     * @param name name of the state
     */
    State (String name){
        this.name=name;
    }
    
    /**
     * Constructor for a state with a parent
     * @param name name of the state
     * @param parent parent of the state
     */
    State (String name, CompositeState parent){
        this.name=name;
        this.parent=parent;
    }

    /**
     * Getter for the state name
     * @return string with the name of the state
     */
    public String getName(){
        return this.name;
    }
    
    /**
     * 
     * @param destination
     * @param c
     * @return
     */
    public Boolean addTransition(State destination, Color c){
        ImmediateTransition t = new ImmediateTransition(this, destination, c);
        if(this.itransition!=null){
            return false;
        }
        this.itransition=t;
        return true;
    }

    public Boolean addTransition(State destination, String e){
        TriggeredTransition t = new TriggeredTransition(this, destination, e);
        for (TriggeredTransition tt : this.ttransitions){
            if (tt.getEvent().equals(t.getEvent())){
                return false;
            }
        }
        this.ttransitions.add(t);
        return true;
    }

    
    public Transition getTTransition(String s){
        for (TriggeredTransition t : this.ttransitions){
            if (t.getEvent().equals(s)){
                return t;
            }
        }
        if (this.parent!=null){
            return this.parent.getTTransition(s);
        }
        return null;
    }

    public Transition getITransition(){
        return this.itransition;
    }


    /**
     * Method that gets all the transition in su
     * @return
     */
    public List<Transition> getTransitions(){
        List<Transition> transitions = new ArrayList<>();
        transitions.addAll(this.ttransitions);
        if (itransition!=null){
            transitions.add(this.itransition);
        }
        return transitions;
    }

    /**
     * Method that returns the initial node (just an empty method here)
     */
    public SimpleState getInitial(){
        return null;
    }

    /**
     * Method that returns the state in the UML notation to generate plantuml
     */   
    public String getUML(){
        return "state "+this.getName();
    }

    /**
     * Passsing the class to a string
     */
    @Override
    public String toString(){
        return ("State["+this.getName());
    }

}