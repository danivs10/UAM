package src.list;

import java.util.*;

/**
 * Class for the SortedList.
 * @author Pablo Sancho & Daniel Varela
 * @version 1.0
 */
public class SortedList<T extends Comparable<T>> extends ArrayList<T> {

    private ArrayList<Comparator<T>> comparators = new ArrayList<Comparator<T>>();
    private Comparator<T> comparator = new Comparator<T>() {
        @Override
        public int compare(T o1, T o2) {
            int result = 0;
            result = o1.compareTo(o2);
            if (result!=0) {
                return result;
            }
            for (Comparator<T> comparator : comparators) {
                result = comparator.compare(o1, o2);
                if (result != 0) {
                    break;
                }
            }
            return result;
        }
    };

    /**
     * Constructor for the SortedList class.
     * @param list List of the elements to be added initially to the list.
     */
    public SortedList(List<T> list) {
        super(list);
        this.sort(this.comparator);
    }

    /**
     * Method to add a criterion to the list of comparators.
     * @param criterion Comparator to be added.
     */
    public void addCriterion(Comparator<T> criterion) {
        this.comparators.add(criterion);
        this.sort(this.comparator);
    }




        
}
