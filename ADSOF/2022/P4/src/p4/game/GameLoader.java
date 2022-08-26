package p4.game;

import java.io.*;
import java.util.*;

public class GameLoader {
    /**
     * Loads a game from a file
     * @param string the name of the file to load
     * @return the loaded game
     */
    public static Game load(String string) throws IOException {
        List<Integer> numbers = new ArrayList<>();

        Game g = null;

        File f = new File(string);

        try  (Scanner entrada = new Scanner(f)) {

            

            for(int i=0; i<3; i++) {
                numbers.add(entrada.nextInt());            
            }

            g=new Game(numbers.get(1), numbers.get(0), numbers.get(2));

        } catch (FileNotFoundException e) {
            System.out.println(e.toString());
        } catch (Exception e) {
            System.out.println(e.toString());
        }

        return g;
    }
}
