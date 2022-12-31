import java.io.*;
import java.util.ArrayList;

class Day3 {
	public static char getCommonChar(String firstHalf, String secondHalf) {
		if (firstHalf.length() != secondHalf.length()) {
			throw new IllegalArgumentException("Strings in getCommonChar() are unequal");
		}

		char c = '\0';
		for (char ch: firstHalf.toCharArray()) {
			if (secondHalf.indexOf(ch) != -1) {
				c = ch;				
			}
		}
		return c;
	}

	public static int getCharValue(char c) {
		int val = c;
		if (val >= 97 && val <= 122) { // Lowercase
			val -= 96;
		} else if (val >= 65 && val <= 90) { // Uppercase
			val -= 38;			  	   
		} else {
			throw new RuntimeException("Something went wrong. Unexpected character encountered.");
		}
		return val;
	}

	public static void main(String[] args) {
		try {
			BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
			ArrayList<String> lines = new ArrayList<String>();

			String line = "";
			while ((line = reader.readLine()) != null) {
				lines.add(line);
			}

			int sum = 0;
			for (String s : lines) {
				String firstHalf = s.substring(0, s.length() / 2);
				String secondHalf = s.substring(s.length() / 2, s.length());
				char c = getCommonChar(firstHalf, secondHalf);
				sum += getCharValue(c);
			}
			System.out.println(sum); // Part 1
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}
}
