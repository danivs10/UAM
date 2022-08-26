package tests;

import java.util.List;
import src.*;

public class StateMachineTest4 {
	public static void main(String[] args) {
		StateMachine musicSystem = createMusicSystemWithHierarchy();

		for (State s : musicSystem.states()) 
			System.out.println("Transitions from: "+s.getName()+": "+s.getTransitions());
		
		System.out.println("\n"+musicSystem+"\n");			
		musicSystem.simulate(List.of("power", "mode", "mode", "power"));
	}

	public static StateMachine createMusicSystemWithHierarchy() {
		StateMachine musicSystem = new StateMachine("Music System");
		musicSystem.createState("starting", "Starting the music system");
		CompositeState cs = musicSystem.createCompositeState("On");
		cs.createState("CD");	
		cs.createState("Tuner");
		musicSystem.createState("off");
		
		musicSystem.addEvents("mode", "power");
		
		musicSystem.connect("starting", "On", Color.RED);		// immediate transition
		cs.connect("Tuner", "CD", "mode");
		cs.connect("CD", "Tuner", "mode");
		musicSystem.connect("On", "off", "power");
		musicSystem.connect("off", "starting", "power");
		
		musicSystem.setInitial("off");
		cs.setInitial("Tuner");
		return musicSystem;
	}
}
