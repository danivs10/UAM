package tests;

import java.io.FileNotFoundException;
import src.*;

public class StateMachineTest5 {
	public static void main(String[] args) throws FileNotFoundException {
		StateMachine musicSystem = StateMachineTest4.createMusicSystemWithHierarchy();
		musicSystem.toPlantUML("MusicSystem.txt");
	}
}
