import java.io.*;
import java.util.ArrayList;

class Day2 {
	public static int parseRound(String enemyPlay, String yourPlay) {
		int roundScore = 0;

		// Rock - A/X
		// Paper - B/Y
		// Scissors - C/Z

		// Score from yourPlay
		switch (yourPlay) {
			case "Y":
				roundScore += 2;
				break;
			case "X":
				roundScore += 1;
				break;
			case "Z":
				roundScore += 3;
				break;
			default:
				throw new RuntimeException("Something went wrong.");
		}
		
		// Score from match outcome
		switch (enemyPlay) {
			case "A":
				if (yourPlay.equals("Y")) {
					roundScore += 6; // Win	
				} else if (yourPlay.equals("X")) {
					roundScore += 3; // Draw
				}
				break;
			case "B":
				if (yourPlay.equals("Z")) {
					roundScore += 6; // Win
				} else if (yourPlay.equals("Y")) {
					roundScore += 3; // Draw
				}
				break;
			case "C":
				if (yourPlay.equals("X")) {
					roundScore += 6; // Win
				} else if (yourPlay.equals("Z")) {
					roundScore += 3; // Draw	
				}
				break;
			default:
				throw new RuntimeException("Something went wrong.");
		}	
		return roundScore;
	}

	public static int parseRoundTwo(String enemyPlay, String yourPlay) {
		int roundEndNeeded = 0; // Win/1, Lose/2, Draw/3
		switch (yourPlay) {
			case "X":
				roundEndNeeded = 2;
				break;
			case "Y":
				roundEndNeeded = 3;
				break;
			case "Z":
				roundEndNeeded = 1;
				break;
			default:
				throw new RuntimeException("Something went wrong.");
		}

		int roundScore = 0;
		switch (enemyPlay) {
			case "A":
				if (roundEndNeeded == 1) {
					roundScore += 2 + 6;	
				} else if (roundEndNeeded == 2) {
					roundScore += 3;
				} else {
					roundScore += 1 + 3;
				}
				break;
			case "B":
				if (roundEndNeeded == 1) {
					roundScore += 3 + 6;	
				} else if (roundEndNeeded == 2) {
					roundScore += 1;
				} else {
					roundScore += 2 + 3;
				}
				break;
			case "C":
				if (roundEndNeeded == 1) {
					roundScore += 1 + 6;	
				} else if (roundEndNeeded == 2) {
					roundScore += 2;
				} else {
					roundScore += 3 + 3;
				}
				break;
			default:
				throw new RuntimeException("Something went wrong");
		}
		return roundScore;
	}

	public static void main(String[] args) {
		ArrayList<String> enemyPlay = new ArrayList<String>();
		ArrayList<String> yourPlay = new ArrayList<String>();
		
		try {
			BufferedReader reader = new BufferedReader(new FileReader("input.txt"));

			// Gather up enemy play and response play into 2 separate arrayLists
			String line = "";
			while ((line = reader.readLine()) != null) {
				String[] round = line.split("\\s+");
				enemyPlay.add(round[0]);
				yourPlay.add(round[1]);
			}
		} catch (IOException e) {
			throw new RuntimeException(e);	
		}	
		
		int yourScore = 0;
		int rounds = enemyPlay.size();
		for (int i = 0; i < rounds; i++) {
			yourScore += parseRound(enemyPlay.get(i), yourPlay.get(i));
		}
		// Part 1
		System.out.println(yourScore);

		// X - lose
		// Y - draw
		// Z - win
		yourScore = 0;
		for (int i = 0; i < rounds; i++) {
			yourScore += parseRoundTwo(enemyPlay.get(i), yourPlay.get(i));	
		}
		System.out.println(yourScore);
	}
}
