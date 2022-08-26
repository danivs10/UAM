package tests;

import src.*;

public class StateMachineTest2 {
	public static void main(String[] args) {
		StateMachine musicSystem = createMusicSystem();		
		// not valid, power already goes to off
		System.out.println(musicSystem.connect("CD", "starting", "power"));
		// not valid, foo is not a valid event
		System.out.println(musicSystem.connect("CD", "starting", "foo"));
		
		for (State s : musicSystem.states()) 
			System.out.println("Transitions from: "+s.getName()+": "+s.getTransitions());
	}

	public static StateMachine createMusicSystem() {
		StateMachine musicSystem = new StateMachine("Music System");
		musicSystem.createState("starting", "Starting the music system");		
		musicSystem.createState("CD");	// description is optional
		musicSystem.createState("Tuner");
		musicSystem.createState("off");
				
		musicSystem.addEvents("mode", "power");
		
		musicSystem.connect("starting", "Tuner", Color.RED);		// immediate transition
		musicSystem.connect("Tuner", "CD", "mode");
		musicSystem.connect("CD", "Tuner", "mode");
		musicSystem.connect("CD", "off", "power");
		musicSystem.connect("Tuner", "off", "power");
		musicSystem.connect("off", "starting", "power");
		return musicSystem;
	}
}
