package src.list;
import java.io.FileWriter;
import java.io.File;
import java.io.IOException;
import java.util.function.Function;

/**
 * Class for the FilePersister.
 * @author Pablo Sancho & Daniel Varela
 * @version 1.0
 */
public class FilePersister<T> implements IOption<T> {
    private Function<T, String> func;

    /**
     * Constructor for the FilePersister class.
     * @param func Function to be applied to the object.
     * @param fileName Name of the file.
     */
    public FilePersister(Function<T, String> f) {
        this.func = f;
    }

    /**
     * Method to apply to the letters.
     * @param o Object to be printed.
     * @return String with the letter modified.
     */
    public String apply(T o, String message) {
        String fname = "";
        String name = "";
        int id=0;
        File f;
        name = this.func.apply(o);
        fname = name + id + ".txt";
        f = new File(fname);
        while (f.exists()) {
            id++;
            fname = name + id + ".txt";
            f = new File(fname);
        }
        try {
            f.createNewFile();
            FileWriter fw = new FileWriter(f);
            fw.write(message); 
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return message;
    }
}
