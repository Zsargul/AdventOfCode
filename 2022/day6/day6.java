import java.io.*;
import java.util.*;

class Day6 {
	public static boolean noDuplicates(LinkedList<Character> chars) {
		if (chars.size() != 4) throw new IllegalArgumentException("Error: chars list in noDuplicates() is not of size 4");
		char a = chars.get(0);
		char b = chars.get(1);
		char c = chars.get(2);

		for (int i = 1; i <= 3; i++) {
			if (a == chars.get(i)) return false;
		}
		for (int i = 2; i <= 3; i++) {
			if (b == chars.get(i)) return false;
		}
		if (c == chars.get(3)) return false;

		return true;
	}

	public static boolean noDuplicatesMessage(LinkedList<Character> chars) {
		if (chars.size() != 14) throw new IllegalArgumentException("Error: chars list in noDuplicates() is not of size 4");

		Set<Character> set = new HashSet<>();
		char[] characters = convertToCharArray(chars);
		
		for (Character c  : characters) {
			if (!set.add(c)) {
				return false;
			}
		}
		return true;
	}

	public static char[] convertToCharArray(LinkedList<Character> chars) {
		int l = chars.size();
		char[] charArray = new char[l];

		for (int i = 0; i < l; i++) {
			charArray[i] = chars.get(i);
		}

		return charArray;
	}

	public static void main(String args[]) {
		int r = 0;
		try {
			// Part 1
			BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
			
			int c = 0;
			boolean fourPushed = false;
			LinkedList<Character> chars = new LinkedList<Character>();
			while ((r = reader.read()) != -1) {
				chars.add((char)r);
				c++;

				if (fourPushed) {
					if (noDuplicates(chars)) break;
					chars.removeFirst();
				} else {
					if (chars.size() == 3) {
						fourPushed = true;
					}
				}
			}
			System.out.println(c); 

			// Part 2
			BufferedReader reader2 = new BufferedReader(new FileReader("input.txt"));

			LinkedList<Character> msg = new LinkedList<Character>();
			int ch = 0;
			int count = 0;
			for (int i = 0; i < 14; i++) {
				if ((ch = reader2.read()) != -1) {
					msg.add((char)ch);
					count++;
				}
			}
			while ((ch = reader2.read()) != -1) {
				if (noDuplicatesMessage(msg)) break;
				msg.removeFirst();
				msg.add((char)ch);
				count++;
			}
			System.out.println(count);
		} catch (IOException ex) {
			throw new RuntimeException(ex);
		}
	}
}
