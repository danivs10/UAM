package tests;

import java.io.IOException;

import p4.exception.*;
import p4.game.*;

public class GameMainFromFile {
	
	public static void main(String args[]) throws InvalidGame, IOException{

		Game g = GameLoader.load(args[0]);
		if (g != null) 
			g.play();

	}

}
