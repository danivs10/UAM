package src.list;

import java.util.*;
import java.util.function.*;

/**
 * Class that represents a letter.
 * @author Pablo Sancho & Daniel Varela
 * @version 1.0
 */
public class Letter<T> {
    private String letter;
    private List<Function<T, Object>> l = new ArrayList<>();

    /**
     * Constructor for the Letter class.
     * @param letter String to be printed.
     * @param l List of functions to be applied to the object.
     */
    public Letter(String string, List<Function<T, Object>> f) {
        this.letter = string;
        this.l = f;
    }

    /**
     * Method to emit the letter.
     * @param o Object to be printed.
     * @return String with the letter.
     */
    public String emit(T o){
        String output="";
        int i=0;
        String[] auxstr;
        i=0;
        auxstr=this.letter.split("##");
        for (String s : auxstr){
            if (i==0){
                output+=s;
            }
            else if (l.get(i-1)!=null){
                output+=l.get(i-1).apply(o)+s;
            }
            else{
                output+="##"+s;
            }
            i++;
        }
            output+="\n";
        
        return output;
    }

    /**
     * Method to get the letter.
     * @return String with the letter.
     */
    public String getLetter(){
        return this.letter;
    }


    
}
