package src.list;

import java.util.List;
import java.util.function.Function;

/**
 * Class for the Each type of letter.
 * 
 * @author Pablo Sancho & Daniel Varela
 * @version 1.0
 */
public class Each<T, V> extends Letter<T> {
    private Function<T, List<V>> f;
    private List<Function<V, Object>> l;

    /**
     * Constructor for the Each class.
     * 
     * @param f      Function to be applied to the object.
     * @param string String to be printed.
     * @param l      List of functions to be applied to the object.
     */
    public Each(Function<T, List<V>> f, String string, List<Function<V, Object>> l) {
        super(string, null);
        this.f = f;
        this.l = l;
    }

    /**
     * Method to emit the letter.
     * 
     * @param o Object to be printed.
     * @return String with the letter.
     */
    @Override
    public String emit(T o) {
        /* apply the function f to the object o */
        List<V> lis = f.apply(o);
        String output = "";
        int i = 0;
        String[] auxstr;
        auxstr = super.getLetter().split("##");
        for (V e : lis) {
            i = 0;
            for (String s : auxstr) {
                if (i == 0) {
                    output += s;
                } else if (this.l.get(i - 1) != null) {
                    output += this.l.get(i - 1).apply(e) + s;
                } else {
                    output += "##" + s;
                }
                i++;
            }
            output += "\n";

        }
        return output;

    }

}
