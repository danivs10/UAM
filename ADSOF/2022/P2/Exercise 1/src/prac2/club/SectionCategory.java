package prac2.club;

/**
 * Enumeration of the different types of sections that there are.
 * @author Daniel Varela
 */
public enum SectionCategory {
	HISTORICAL, NEW, UNKNOWN;
	
	private static final int RECENT = 2000;
	
	/**
	 * Method to get the type of section depending on the year
	 * @param year which is gonna decide the type of category 
	 * @return type of SectionCategory
	 */
	public static SectionCategory getCategory(int year) {
		if (year < RECENT) 
			return HISTORICAL;
		else 
			return NEW;
	}
}
