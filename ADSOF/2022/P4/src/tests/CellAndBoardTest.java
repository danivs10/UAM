package tests;
import p4.exception.*;
import p4.tokens.*;
import p4.interfaces.*;
import p4.game.*;

public class CellAndBoardTest {
	
	public static void main(String args[]) {		
		Player p1 = new Player();
		Player p2 = new Player();
		IBoard board = new BoardGame(10, p1, p2);
		System.out.println(board);
		
		try {
		
			board.addToken(0, 0, new FixedToken(p1));
			System.out.println(board);
			board.addToken(0, 0, new FixedToken(p2));
		
		} catch (ForbiddenToken e) {
		
			System.out.println(e);
		
		}
		System.out.println(board);

	}

		
}


