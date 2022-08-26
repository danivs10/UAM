package prac2.club;

/**
 * Abstract class that manages the common information of the Waterpolo, Padel and Soccer classes.
 * @author Daniel Varela
 */
public abstract class Section {
	private String code;
	private int yearFederate;
	
	/**
	 * Constructor of the Section class
 	 * @param cod the code of the Section
 	 * @param year the year of federation of the team
	 */
	public Section(String cod, int y) {
		this.code = cod;
		this.yearFederate = y;
	}
	
	
	/** 
	 * Default method to print the information of a Section object.
	 * @return String
	 */
	@Override public String toString() {
		return "code " + this.code + ", year of federation " + this.yearFederate + ", with " +
				this.numberOfPlayers() + " player(s) per team, category: " + this.getCategory();
	}
	
	/**
	 * Method to be implemented
	 * @return number of players
	 */
	public abstract int numberOfPlayers();
	
	
	/** 
	 * Method to get the category depending on the year of federation.
	 * @return SectionCategory
	 */
	public SectionCategory getCategory() {
		return SectionCategory.getCategory(this.yearFederate);
	}

}
