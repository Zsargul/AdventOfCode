import java.io.*;
import java.util.ArrayList;

class Day1 {
	public static int getTopThreeSum(ArrayList<Integer> caloryList) {
		int first = 0;
		int second = 0;
		int third = 0;
		for (int n : caloryList) {
			if (n > first) {
				third = second;
				second = first;
				first = n;
			} else if (n > second) {
				third = second;
				second = n;
			} else if (n > third) {
				third = n;
			}
		}
		return first+second+third;
	}

	public static int getMaxCalories(ArrayList<Integer> caloryList) {
		int max = 0;
		for (int n : caloryList) {
			if (n > max) {
				max = n;
			}
		}
		return max;
	}

	public static int countLines(String f) {
		int lines = 0;
		try {
			BufferedReader r = new BufferedReader(new FileReader(f));
			while (r.readLine() != null) lines++;
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		return lines;
	}

	public static void main(String[] args) {
		try {
			BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
			
			// Empty ArrayList for each of our elves
			ArrayList<Integer> elvesCalories = new ArrayList<Integer>(); 

			int lines = countLines("input.txt");
			int calories = 0; int lineCount = 1;
			String line;
			while ((line = reader.readLine()) != null) {
				if (!(line.trim().equals(""))) {
					calories += Integer.parseInt(line);
				}

				if (lines == lineCount || line.trim().equals("")) {
					elvesCalories.add(calories);
					calories = 0;
				}
				lineCount++;
			}

			// Part 1
			System.out.println(getMaxCalories(elvesCalories));
			// Part 2
			System.out.println(getTopThreeSum(elvesCalories));
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}
}

