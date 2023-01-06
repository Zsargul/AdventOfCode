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

	public static ArrayList<String> getInstructions(String file) {
		ArrayList<String> ins = new ArrayList<String>();

		try {
			BufferedReader reader = new BufferedReader(new FileReader(file));
			
			String line = "";
			boolean begin = false;
			while ((line = reader.readLine()) != null) {
				if (begin && !line.isEmpty()) {
					ins.add(line);
				}

				if (line.trim().startsWith("1") && !begin) {
					begin = true;
				}
			}
			if (ins.isEmpty()) {
				System.out.println("Warning: Instructions arrayList being returned is empty!");
			}
			return ins;
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
		ArrayList<Stack<Character>> stacks2 = new ArrayList<Stack<Character>>();

		// Populate stacks arrayList with empty stacks
		for (int i = 0; i < stackCount; i++) {
			Stack<Character> s = new Stack<Character>();
			Stack<Character> s2 = new Stack<Character>();
			stacks.add(s);	
			stacks2.add(s2);
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
				stacks2.get(stackNum-1).push(c);
				stackNum++;
			}
		}

		// Gather up instructions for moving stack elements
		ArrayList<String> instructions = getInstructions("input.txt");

		for (String inst : instructions) {
			int elementsToMove, source, destination;
			
			inst = inst.substring(5);
			elementsToMove = Integer.parseInt(inst.substring(0, inst.indexOf(" ")));
			inst = inst.substring(inst.indexOf(" ")+6);
			source = Integer.parseInt(inst.substring(0, inst.indexOf(" ")));
			inst = inst.substring(inst.indexOf(" ")+4);
			destination = Integer.parseInt(inst);

			// Dealing with stacks from part 1
			for (int i = 0; i < elementsToMove; i++) {
				// Move element from top of source to destination
				stacks.get(destination-1).push(stacks.get(source-1).peek());	
				// Pop off moved element from the top of the source
				stacks.get(source-1).pop();
			}	

			// Dealing with stacks from part 2
			if (elementsToMove == 1) {
				stacks2.get(destination-1).push(stacks2.get(source-1).peek());
				stacks2.get(source-1).pop();
			} else {
				Stack<Character> tempSource = new Stack<Character>();

				// Copy and pop the elements to move into the temporary source
				for (int i = 0; i < elementsToMove; i++) {
					tempSource.push(stacks2.get(source-1).peek());
					stacks2.get(source-1).pop();
				}

				// Move elements in new order
				for (int i = 0; i < elementsToMove; i++) {
					stacks2.get(destination-1).push(tempSource.peek());
					tempSource.pop();
				}
			}
		}

		// Construct final messages
		String msg = "";
		for (Stack st : stacks) {
			msg += st.peek();
		}

		String msg2 = "";
		for (Stack st : stacks2) {
			msg2 += st.peek();
		}
		System.out.println(msg); // Part 1
		System.out.println(msg2); // Part 2
	}
}
