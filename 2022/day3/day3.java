import java.io.*;
import java.util.ArrayList;

class Day3 {
	public static char getCommonChar(String firstHalf, String secondHalf) {
		if (firstHalf.length() != secondHalf.length()) {
			throw new IllegalArgumentException("Strings in getCommonChar() are unequal");
		}

		char c = '\0';
		for (char ch : firstHalf.toCharArray()) {
			if (secondHalf.indexOf(ch) != -1) {
				c = ch;				
			}
		}
		return c;
	}

	public static char getCommonChar2(String one, String two, String three) {
		char c = '\0';
		for (char ch : one.toCharArray()) {
			if (two.contains(Character.toString(ch)) && three.contains(Character.toString(ch))) {
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

			// Gather up linse into groups of 3
			if (lines.size() % 3 != 0) {
				throw new RuntimeException("The number of lines is not a multiple of 3");
			}

			ArrayList<ArrayList<String>> groups = new ArrayList<ArrayList<String>>();
			for (int i = 0; i < lines.size(); i += 3) {
				ArrayList<String> group	= new ArrayList<String>();
				group.add(lines.get(i));
				group.add(lines.get(i+1));
				group.add(lines.get(i+2));
				groups.add(group);
			}

			// Find common characters
			sum = 0;
			for (ArrayList group : groups) {
				String a = group.get(0).toString();
				String b = group.get(1).toString();
				String c = group.get(2).toString();
				char common = getCommonChar2(a, b, c);
				sum += getCharValue(common);	
			}
			System.out.println(sum); // Part 2

		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}
}
