package tests;
import java.util.*;
import p4.tokens.*;
import p4.interfaces.*;
import p4.game.*;

public class TokensAndPlayersTest {
	
	public static void main(String args[]) {
		Player fstPlayer = new Player();
		Player sndPlayer = new Player();
		
		List<IToken> tokensPlayerOne = List.of(new NormalToken(fstPlayer), new FixedToken(fstPlayer));
		List<IToken> tokensPlayerTwo = List.of(new MultiplierToken(sndPlayer));

		
		for (IToken t: tokensPlayerOne) {
			System.out.println(t + " " + t.canBeOverwritten());
		}

		
		IToken enhancer = new EnhancerToken();
		System.out.println(enhancer + " " + enhancer.canBeOverwritten());
		
		IToken wall = new WallToken();
		System.out.println(wall + " " + wall.canBeOverwritten());

		
		
		for (IToken t: tokensPlayerTwo) {
			System.out.println(t + " " + t.canBeOverwritten());
		}
		
		
	}

}
