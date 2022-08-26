package prac2.club;
/**
 * Class that manages the Soccer objects information
 * @author Pablo Sancho
 */
public class Soccer extends Section {
	private boolean professional;
	
	/**
	 * Constructor of the Soccer class
	 * @param c
	 * @param y
	 * @param professional
	 */
	public Soccer(String c, int y, boolean professional) {
		super(c, y);
		this.professional = professional;
	}
	/**
	 * Method that returns the number of players of the Soccer section
	 */
	@Override public int numberOfPlayers() {
		return 11;
	}
	
	
	/** 
	 * Method to print the information of the Soccer class
	 * @return String
	 */
	@Override public String toString() {
		return "Soccer " + (this.professional ? "professional" : "amateur") + ", " + super.toString();
	}
	
	
	/** 
	 * Method to get the professional attribute of the class.
	 * @return boolean
	 */
	public boolean getProfessional() {
		return this.professional;
	}
	
	
	/** 
	 * Method to set the attribute professional of the class.
	 * @param p true or false depending wether is professional or not.
	 */
	public void setProfessional(boolean p) {
		this.professional = p;
	}
}
