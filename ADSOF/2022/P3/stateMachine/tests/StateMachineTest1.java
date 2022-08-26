package tests;

import src.*;

public class StateMachineTest1 {
	public static void main(String[] args) {
		StateMachine musicSystem = new StateMachine("Music System");
		musicSystem.createState("starting", "Starting the music system");		
		musicSystem.createState("CD");	// description is optional
		musicSystem.createState("Tuner");
		State offState = musicSystem.createState("off");	// return a State	
		// State s = new State("state"); // <- this should raise an error
				
		System.out.println(musicSystem);
		musicSystem.createState("invalid name");  // blank spaces not allowed
		System.out.println(musicSystem);		  // no state added
		
		StateMachine sm = new StateMachine();
		sm.createState("s0");			
		sm.createState("s0");  // repeated names not allowed
		System.out.println(sm);


	}
}
