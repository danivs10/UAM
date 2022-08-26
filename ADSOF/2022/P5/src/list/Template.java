package src.list;

import java.util.*;
import java.util.function.Function;
import java.util.function.Predicate;

/**
 * Generic class that represents Template.
 * @author Pablo Sancho & Daniel Varela
 * @version 1.0
 */
public class Template<T extends Comparable<T>>{
    private SortedList<T> objects = new SortedList<T>(new ArrayList<T>());
    private List<Letter<T>> letters = new ArrayList<>();
    private List<IOption<T>> options = new ArrayList<>();

    Function<String, String> toLowerCase = (var input) -> input.toLowerCase();

    
    /**
     * Method to add an object to the list of letters.
     * @param s String to be added.
     * @param p Functions to be added to complete the String.
     */
    @SuppressWarnings("unchecked")
    public Template<T> add(String s, Function<T, Object>... p) {
        List<Function<T, Object>> l = new ArrayList<>();
        for(Function<T, Object> f : p){
            l.add(f);
        }
        this.letters.add(new Letter<T>(s, l));
        return this;
    }

    /**
     * Method to add a criteria to the sorting on the list of objects SortedList
     * @param c Comparator to be added.
     */
    public void withSortingCriteria(Comparator<T> c) {
        this.objects.addCriterion(c);
    }

    /**
     * Method to add an object to the list of objects.
     * @param o Object to be added.
     */
    @SuppressWarnings("unchecked")
    public Template<T> addObjects(T... t){
        for (T t1 : t) {
            this.objects.add(t1);
        }
        Collections.reverse(this.objects);
        return this;
    }


    /**
     * Method to emit the letters.
     * @return Map with the letters.
     */
    public Map<T, String> emit(){
        Map<T, String> m = new LinkedHashMap<>();
        String msg="";
        for (T o : this.objects){
            msg=this.emit(o);
            for (IOption<T> io : this.options){
                msg=io.apply(o, msg);
            }
            m.put(o, msg);
        }
        return m;
    }
    
    /**
     * Method to emit the letters.
     * @param o Object to be emited.
     * @return String with the letter of the object.
     */
    public String emit(T o){
        String msg="";
        for (Letter<T> l : this.letters){
            msg+=l.emit(o);
        }
        return msg;
    }

    /**
     * Method to add an When letter to the list of letters.
     * @param p Predicate for the when letter.
     * @param s String to be added.
     */
    public Template<T> addWhen(Predicate<T> p, String s){
        this.letters.add(new When<T>(p, s));
        return this;
    }

    /**
     * Method to add an Each letter to the list of letters.
     * @param f Function to obtain the list of objects.
     * @param s String to be added.
     * @param p Functions to be added to complete the String.
     */
    @SuppressWarnings("unchecked")
    public <K> Template<T> addForEach(Function<T, List<K>> f, String s, Function<K, Object>... p){
        List<Function<K, Object>> l = new ArrayList<>();
        for(Function<K, Object> f1 : p){
            l.add(f1);
        }
        Collections.reverse(l);
        this.letters.add(new Each<T, K>(f, s, l));
        return this;
    }

    /**
     * Method to add options to the list of options.
     * @param o Option to be added.
     */
    @SuppressWarnings("unchecked")
    public void withOptions(IOption<T>... o){
        for(IOption<T> i : o){
            this.options.add(i);
        }
    }

    

}
