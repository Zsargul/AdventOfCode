import java.io.*;
import java.util.*;

class Day7 {
	public static boolean isCommand(String s) {
		return s.trim().startsWith("$") ? true : false;
	}

	public static void main(String args[]) {
		ArrayList<String> lines = new ArrayList<String>();
		int maxSize = 100000;

		Hashtable<String, Integer> dirDict = new Hashtable<String, Integer>();

		// Extract input lines
		try {
			BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
			String line = "";
			while ((line = reader.readLine()) != null) {
				lines.add(line);
			}

		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		String l = "";
		String cmd = "";
		String temp = "";
		boolean listMode = false;

		Stack<String> dirDepth = new Stack<String>();
		dirDict.put("/", 0);
		dirDepth.push("/");
		for (int i = 1; i < lines.size(); i++) {
			l = lines.get(i);
			String[] parts = l.split(" ");

			System.out.print(l+"        ");
			if (isCommand(l)) {
				cmd = parts[1];
				switch (cmd) {
					// Change Directory
					case "cd":
						listMode = false;
						if (parts[2].equals("..")) { 
							temp = dirDepth.pop();

							System.out.println("[Curr]: "+dirDepth.peek()+" | [Prev]: "+temp);
							dirDict.put(dirDepth.peek(), dirDict.get(dirDepth.peek())+dirDict.get(temp));
						} else {
							System.out.println("[Curr]: "+parts[2]+" | [Prev]: "+dirDepth.peek());
							if (!dirDict.containsKey(parts[2])) { // Directory has not yet been encountered
								dirDict.put(parts[2], 0);
							}

							dirDepth.push(parts[2]);
						}
						break;

					// List Directory Contents
					case "ls":
						System.out.println("");
						listMode = true;
						continue;

					// Unknown Command
					default:
						throw new IllegalArgumentException("Error: Unknown command encountered. Ending file system scan.");
				}
			} else if (listMode) {
				System.out.println("");
				if (parts[0].equals("dir")) {
					// Add directory if has not yet been encountered
					if (!dirDict.containsKey(parts[1])) {
						dirDict.put(parts[1], 0);
					} 
				} else {
					dirDict.put(dirDepth.peek(), dirDict.get(dirDepth.peek())+Integer.parseInt(parts[0]));
				}
			}
		}
		while (dirDepth.peek() != "/") {
			temp = dirDepth.pop();

			dirDict.put(dirDepth.peek(), dirDict.get(dirDepth.peek())+dirDict.get(temp));
		}

		int sum = 0;
		Set<String> keys = dirDict.keySet();
		for (String key : keys) {
			System.out.println(key + " (Size: " + dirDict.get(key)+")");
			if (dirDict.get(key) <= maxSize) sum += dirDict.get(key);
		}
		System.out.println(sum);
	}
}
