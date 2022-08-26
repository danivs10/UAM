package prac2.club;

/**
 * Class that manages all the information about Waterpolo objects
 * @author Pablo Sancho
 */
public class Waterpolo extends Section{
    private boolean national;
    private String locationOfTraining;

    /**
     * Constructor of the Waterpolo class.
     * @param cod code of the league
     * @param a year of federation
     * @param national if it is national or not
     * @param locationOfTraining the location of training of the team
     */
    public Waterpolo(String cod, int a, boolean national, String locationOfTraining) {
        super(cod, a);
        this.national=national;
        this.locationOfTraining=locationOfTraining;
    }

    
    /** 
     * Method to get the number of players of the team
     * @return int 
     */
    @Override
    public int numberOfPlayers() {
        return 6;
    }

    
    /** 
     * Method to print the information about the waterpolo team.
     * @return String
     */
    @Override
    public String toString(){
        return "Waterpolo " + (this.national ? "national" : "regional") + ", " + super.toString();
        
    }
    
	
    /** 
     * Method to get the location of training of a waterpolo team.
     * @return String
     */
    public String getLocation() {
		return this.locationOfTraining;
	}
	
	
    /** 
     * Method to set the location of training of a waterpolo team.
     * @param location
     */
    public void setLocation(String location) {
		this.locationOfTraining = location;
	}

    
    /** 
     * Method to get the type of league of a waterpolo team.
     * @return boolean
     */
    public boolean getLeague() {
		return this.national;
	}
	
	
    /** 
     * Method to set the type of league.
     * @param national
     */
    public void setLeague(boolean national) {
		this.national = national;
	}

	
    /** 
     * Method to get the type of category of this type of object.
     * @return SectionCategory
     */
    @Override public SectionCategory getCategory() {
		return SectionCategory.NEW;
	}
}
