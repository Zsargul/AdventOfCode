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
		String curDir = "";
		String prevDir = "";
		for (int i = 0; i < lines.size(); i++) {
			l = lines.get(i);
			String[] parts = l.split(" ");

			if (isCommand(l)) {
				cmd = parts[1];
				switch (cmd) {
					// Change Directory
					case "cd":
						if (parts[2].equals("..")) { 
							curDir = prevDir;
						} else {
							prevDir = curDir;
							curDir = parts[2];

							if (!dirDict.containsKey(parts[2])) { // Directory has not yet been encountered
								dirDict.put(parts[2], 0);
							}
						}
						break;

					// List Directory Contents
					case "ls":

						break;

					// Unknown Command
					default:
						throw new IllegalArgumentException("Error: Unknown command encountered. Ending file system scan.");
				}
			} else {
					
			}
		}
	}
}
