package src;
import java.io.FileWriter; 
import java.io.IOException;
import java.io.FileNotFoundException;


import java.util.*;

/**
 * Class to manage the StateMachine objects
 * @author Pablo Sancho & Daniel Varela
 */
public class StateMachine {
    private String name = null;
    private List<State> states = new ArrayList<>();
    private List<String> events = new ArrayList<>();
    private State initialState = null;

    /**
     * Constructor of a StateMachine with a given name.
     * @param name name of the StateMachine.
     */
    public StateMachine(String name) {
        this.name = name;
    }

    /**
     * Constructor of a StateMachine without name.
     */
    public StateMachine() {
        this.name = "StateMachine";
    }

    /**
     * Method to return the list of states of the State Machine
     * @return
     */
    public List<State> states() {
        return this.states;
    }

    /**
     * Method to create a SimpleState given its name and description.
     * @param name name of the state.
     * @param description description of the state.
     * @return initialized SimpleState.
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
     * Method to create a SimpleState given its name.
     * @param name name of the state.
     * @return initialized SimpleState.
     */
    public SimpleState createState(String name) {
        SimpleState auxState = null;
        if (checker(name)) {
            auxState = new SimpleState(name);
            this.states.add(auxState);
            return auxState;
        }
        return null;

    }

    /**
     * Method to create a CompositeState.
     * @param name name of the state.
     * @return new CompositeState.
     */
    public CompositeState createCompositeState(String name) {
        CompositeState auxState = null;
        if (checker(name)) {
            auxState = new CompositeState(name);
            this.states.add(auxState);
            return auxState;
        }
        return null;

    }

    /**
     * Method to check if a name is valid.
     * @param name name to be evaluated.
     * @return true or false depending whether on it's valid or not.
     */
    public boolean checker(String name) {
        return (name != null && name.matches("^[a-zA-Z0-9]*$") && stateChecker(name));
    }

    /**
     * Method to check if a state given its name aready exists.
     * @param name name of the state.
     * @return true or false depending whether on if it exists.
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
     * Method to get an state by its name.
     * @param name name of the state to be searched.
     * @return State if it exists, if not null.
     */
    public State getStateByName(String name) {
        for (State s : this.states) {
            if (s.getName().equals(name)) {
                if(s.getInitial()!=null){
                    return s.getInitial();
                }
                return s;
            }
        }
        return null;
    }

    /**
     * Method to add a ImmediateTransition to a state.
     * @param source source state.
     * @param destination destination state.
     * @param c color of the Transition.
     * @return true or false.
     */
    public Boolean connect(String source, String destination, Color c) {
        if (!this.connectionCheck(source, destination)) {
            return false;
        }
        return this.getStateByName(source).addTransition(getStateByName(destination), c);
    }

    /**
     * Method to add a TriggeredTransition to a state.
     * @param source source state.
     * @param destination destination state.
     * @param s string of the Transition.
     * @return true or false.
     */
    public Boolean connect(String source, String destination, String s) {
        if (!this.connectionCheck(source, destination) || !this.events.contains(s)) {
            return false;
        }
        return this.getStateByName(source).addTransition(getStateByName(destination), s);

    }

    /**
     * Method to add one or more events to the StateMachine.
     * @param e events to be added.
     * @return true or false .
     */
    public Boolean addEvents(String... e) {
        for (String event : e) {
            if (this.events.contains(event)) {
                return false;
            }
            this.events.add(event);
        }
        return true;
    }

    /**
     * Method to check if two states are already connected.
     * @param source source state.
     * @param destination destination state.
     * @return true or false.
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
     * Method to set the initial state of an StateMachine.
     * @param string name of the state.
     * @return true or false.
     */
    public Boolean setInitial(String string) {
        if (this.getStateByName(string).equals(null)) {
            return false;
        }
        this.initialState = this.getStateByName(string);
        return true;
    }
    
    /**
     * Method to check if a list of events exists in a StateMachine.
     * @param of list of events.
     * @return true or false.
     */
    public boolean checkEvents(List<String> of){
        for(String event: of){
            if(!(this.events.contains(event))){
                System.out.println("Error: invalid event "+event);
                return false;
            }
        }
        
        return true;
    }

    /**
     * Method to simulate a StateMachine following the given events.
     * @param of list of events.
     */
    public void simulate(List<String> of) {
        State current=this.initialState;
        int i=0;
        if(checkEvents(of)){
            while (i<of.size()){
                if(current.getTTransition(of.get(i))!=null){
                    System.out.println(current.getName()+current.getTTransition(of.get(i)));
                    current=current.getTTransition(of.get(i)).getDestination().getInitial();
                    i++;
                }
                else if (current.getITransition()!=null){
                    System.out.println(current.getName()+current.getITransition());
                    current=current.getITransition().getDestination().getInitial();
                }
                else {
                    System.out.println("Error: there is no transition from "+current.getName()+" named "+of.get(i)+", and no immediate transition was declared for the state");
                    return;
                }
            }   
        }
        return;
    }

    /**
     * Method to print in the file given by the name the PlantUML coding of the machine.
     * @param name name of the file.
     * @throws FileNotFoundException exception if the file doesn't exist.
     */
    public void toPlantUML(String name) throws FileNotFoundException{
        try {
            FileWriter f = new FileWriter("txt/"+name);
                f.write(this.getUML());
                f.close();
        } 
        catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
            throw new FileNotFoundException();
        }
    }

    /**
     * Method to get the initial state of a StateMachine
     * @return initial state or null
     */
    public State getInitial(){
        if (this.initialState.getInitial()!=null){
            return this.initialState.getInitial();
        }
        return this.initialState;
    }

    /**
     * Method that gets the PlantUML code to be printed in a file.
     * @return PlantUML code.
     */
    public String getUML(){
        String ret= "@startuml\n";
        ArrayList<Transition> trans = new ArrayList<>();
        for(State s : this.states){
            ret=ret+s.getUML();
            trans.addAll(s.getTransitions());
        }
        if(this.getInitial()!=null){
            ret+="[*]-->"+this.getInitial().getName()+"\n";
        }
        
        for (Transition t : trans){
            ret+=t.getUML();
        }
        return ret+"@enduml\n";
    }


    /**
     * Method that prints all the information of a StateMachine
     */
    @Override
    public String toString() {
        return (this.name + " with States:\n" + states);
    }

}
