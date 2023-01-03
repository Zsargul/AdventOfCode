import java.io.*;
import java.util.ArrayList;

class Day4 {
	// Check if range A is in range B or vice versa
	public static boolean superRange(String rangeA, String rangeB) {
		int minA, maxA;
		int minB, maxB;

		String[] a = rangeA.split("-");
		String[] b = rangeB.split("-");
		minA = Integer.parseInt(a[0]);
		maxA = Integer.parseInt(a[1]);
		minB = Integer.parseInt(b[0]);
		maxB = Integer.parseInt(b[1]);

		if ((minB >= minA && maxB <= maxA) || (minA >= minB && maxA <= maxB)) {
			return true;
		}
		return false;
	}

	// Check if the numbers overlap in any way
	public static boolean overlap(String rangeA, String rangeB) {
		int minA, maxA;
		int minB, maxB;

		String[] a = rangeA.split("-");
		String[] b = rangeB.split("-");
		minA = Integer.parseInt(a[0]);
		maxA = Integer.parseInt(a[1]);
		minB = Integer.parseInt(b[0]);
		maxB = Integer.parseInt(b[1]);

		if ((minB > maxA) || (minA > maxB )) {
			return false;
		}
		return true;
	}

	public static void main(String args[]) {
		try {
			BufferedReader reader = new BufferedReader(new FileReader("input.txt"));

			ArrayList<String> left = new ArrayList<String>();
			ArrayList<String> right = new ArrayList<String>();
			String line = "";
			while ((line = reader.readLine()) != null) {
				String[] s = line.split(",", 2);
				left.add(s[0]);
				right.add(s[1]);
			}

			if (left.size() != right.size()) {
				throw new RuntimeException("Pair arrays are of unequal size.");
			}

			int count1 = 0;
			int count2 = 0;
			for (int i = 0; i < left.size(); i++) {
				if (superRange(left.get(i), right.get(i))) count1++;
				if (overlap(left.get(i), right.get(i))) count2++;
			}

			System.out.println(count1); // Part 1
			System.out.println(count2); // Part 2
		} catch (IOException e) {
			throw new RuntimeException(e);
		}	
	}
}
