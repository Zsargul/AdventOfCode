import java.io.*;
import java.util.*;

class Day5 {
	public static int getNumStacks(String file) {
		try {
			BufferedReader reader = new BufferedReader(new FileReader(file));
			
			boolean found = false;
			String line = "";
			while ((line = reader.readLine()) != null && !found) {
				if (line.trim().startsWith("1")) {
					found = true;
					String[] stackCount = line.trim().split("\\s+");
					return stackCount.length;	
				}
			}
			System.out.println("Something went wrong. Reached end of file without finding stack count. Returning 0");
			return 0;
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	public static ArrayList<String> getStackSection(String file) {
		ArrayList<String> stackSection = new ArrayList<String>();

		try {
			BufferedReader reader = new BufferedReader(new FileReader(file));

			String line = "";
			while ((line = reader.readLine()) != null) {
				if (line.trim().startsWith("1")) {
					break;
				}
				stackSection.add(line);
			}

			if (stackSection.isEmpty()) {
				System.out.println("Warning: Stack section arrayList being returned is empty!");
			}
			return stackSection;
			
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	public static void main(String args[]) {
		// Get the number of stacks and initialise an arrayList which holds them
		int stackCount = getNumStacks("input.txt");
		ArrayList<Stack<Character>> stacks = new ArrayList<Stack<Character>>();

		// Populate stacks arrayList with empty stacks
		for (int i = 0; i < stackCount; i++) {
			Stack<Character> s = new Stack<Character>();
			stacks.add(s);	
		}

		// Extract the part of the file which holds the stacks
		ArrayList<String> stackSection = getStackSection("input.txt");
		int stackLineLength = (stackCount * 3) + (stackCount - 1);

		// Populate the stacks arrayList with the extracted values
		for (int j = stackSection.size()-1; j >= 0; j--) {
			String line = stackSection.get(j);
			int stackNum = 1;
			for (int i = 1; i < stackLineLength; i+=4) {
				char c = line.charAt(i);
				if (c == ' ') {
					stackNum++;
					continue;
				}
				stacks.get(stackNum-1).push(c);
				stackNum++;
			}
		}


		for (int i = 0; i < stacks.size(); i++) {
			System.out.println(stacks.get(i).toString());
		}

	}
}

