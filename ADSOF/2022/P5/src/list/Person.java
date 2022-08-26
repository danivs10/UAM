package src.list;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

/**
 * Class that represents a Person.
 * 
 * @author Pablo Sancho & Daniel Varela
 * @version 1.0
 */
public class Person implements Comparable<Person> {
    private String name;
    private LocalDate date;
    private List<Mascot> mascotList = new ArrayList<>();

    /**
     * Constructor for the Person class.
     * 
     * @param name String with the name of the person.
     * @param date LocalDate with the date of the persons birth.
     */
    public Person(String name, LocalDate date) {
        this.name = name;
        this.date = date;
    }

    /**
     * Method to get the birth date of the person.
     * 
     * @return String with the birth date of the person.
     */
    public String getBirthDate() {
        return date.toString();
    }

    /**
     * Method to get the name of the person.
     * 
     * @return String with the name of the person.
     */
    public String getName() {
        return name;
    }

    /**
     * Method to get the age of the person.
     * 
     * @return int with the age of the person.
     */
    public int getAge() {
        /*
         * get the age of a person born in date according to the day, hour and month
         * born
         */
        int age = LocalDate.now().getYear() - date.getYear();
        if (LocalDate.now().getMonthValue() < date.getMonthValue()) {
            age--;
        } else if (LocalDate.now().getMonthValue() == date.getMonthValue()) {
            if (LocalDate.now().getDayOfMonth() < date.getDayOfMonth()) {
                age--;
            }
        }

        return age;
    }

    /**
     * Method to get the mascots of the person.
     * 
     * @return List of Mascots that belong to the person.
     */
    public List<Mascot> getMascots() {
        return this.mascotList;
    }

    /**
     * Method to add a mascot to the person.
     * 
     * @param mascot Mascot to be added.
     */
    public void addMascots(Mascot... m) {
        for (Mascot mascot : m) {
            this.mascotList.add(mascot);
        }
    }

    /**
     * Method to compare two persons.
     * 
     * @param p Person to be compared.
     * @return int with the result of the comparison.
     */
    @Override
    public int compareTo(Person o) {
        return this.name.compareTo(o.name);
    }

    /**
     * Method to print the person.
     * 
     * @return String with the person.
     */
    @Override
    public String toString() {
        return name + " (born: " + date + ")";
    }

}
