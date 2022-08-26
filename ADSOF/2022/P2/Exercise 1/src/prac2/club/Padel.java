package prac2.club;

/**
 * Class that manages the Padel information.
 * @author Daniel Varela
 */
public class Padel extends Section{
	
	private boolean doubles;
	private String locationOfTraining;
	/**
	 * Constructor of the Padel Class
	 * @param c code of the league
	 * @param y year of federation
	 * @param doubles if it is in doubles or singles
 	 * @param locationOfTraining The place where the team trains
	 */
    public Padel(String c, int y, boolean doubles, String locationOfTraining) {
		super(c, y);
		this.doubles = doubles;
		this.locationOfTraining = locationOfTraining;
    }

	
	/** 
	 * Method that returns the number of players of this class.
	 * @return int
	 */
	@Override public int numberOfPlayers() {
        if (this.doubles==false)
		    return 1;
        else
		    return 2;
	}
	
	
	/** 
	 * Method that gets the category of the class.
	 * @return SectionCategory
	 */
	@Override public SectionCategory getCategory() {
		return SectionCategory.UNKNOWN;
	}
	
	
	/** 
	 * Method that returns if an object of this class is in doubles or not.
	 * @return boolean
	 */
	public boolean getDoubles() {
		return this.doubles;
	}
	
	
	/** 
	 * Method to set the attribute doubles of the class
	 * @param p
	 */
	public void setDoubles(boolean p) {
		this.doubles = p;
	}

	
	/** 
	 * Method to get the location of training
	 * @return String
	 */
	public String getLocation() {
		return this.locationOfTraining;
	}
	
	
	/** 
	 * Method to set the location of training of a team.
	 * @param location
	 */
	public void setLocation(String location) {
		this.locationOfTraining = location;
	}


	
	/** 
	 * method to print the information of an object of this class.
	 * @return String
	 */
	@Override public String toString() {
		return "Padel " + (this.doubles ? "by pairs" : "individual") + ", " + super.toString();
	}
	
}
