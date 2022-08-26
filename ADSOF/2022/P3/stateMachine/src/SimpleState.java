package src;

/**
 * Class that contains a Simple state
 * @author Pablo Sancho & Daniel Varela
 */
public class SimpleState extends State{
    private String description=null;

    /**
     * Constructor for a simple state without description
     * @param name name of the state
     */
    SimpleState (String name){
        super(name);
    }
    
    /**
     * Constructor for a simple state without description created inside a recursive state
     * @param name name of the state
     * @param parent parent of the state
     */
    SimpleState (String name, CompositeState parent){
        super(name, parent);
    }
    /**
     * Constructor for a simple state with description
     * @param name name of the state
     * @param description description of the state
     */
    SimpleState (String name, String description){
        super(name);
        this.setDescription(description);
    }

    /**
     * Constructor for a simple state with description created inside a recursive state
     * @param name name of the state
     * @param description description of the state
     * @param parent parent of the state
     */
    SimpleState (String name, String description, CompositeState parent){
        super(name, parent);
        this.setDescription(description);
    }
    
    /**
     * Setter for the description of the state
     * @param description description of state
     */
    public void setDescription(String description){
        this.description=description;
    }

    /**
     * Method that returns the state in the UML notation to generate plantuml
     */    
    @Override
    public String getUML(){
        if(this.description!=null){
            return super.getUML()+": "+this.description+"\n";
        }
        return super.getUML()+"\n";
    }

    /**
     * Method that returns the initial node (end of recursion in this case)
     */
    @Override
    public SimpleState getInitial(){
        return this;
    }
    
    /**
     * Passsing the class to a string
     */
    @Override
    public String toString(){
        return (super.toString()+ ((this.description!=null)?(": "+this.description):"")+"]");
    }
}
