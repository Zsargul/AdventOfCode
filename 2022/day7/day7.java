import java.io.*;
import java.util.*;

class Day7 {
	public static boolean isCommand(String s) {
		return s.trim().startsWith("$") ? true : false;
	}

	public static void main(String args[]) {
		ArrayList<String> lines = new ArrayList<String>();
		int maxSize = 100000;

		// Extract input lines EXCLUDING 'ls' command
		try {
			BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
			String line = "";
			while ((line = reader.readLine() != null) {
				if (!line.equals("$ ls")) {
					lines.add(line);
				}
			}
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		String l = "";
		String fileName = ""; int fileSize = 0;
		ArrayList<Directory> directories = new ArrayList<Directory>();
		Stack<Directory> directoryStack = new Stack<Directory>();

		directories.add("/", 0, null);
		directoryStack.push(directories.get(0));
		Directory currentDirectory;

		for (int i = 1; i < lines.size(); i++) {
			currentDirectory = directoryStack.peek();
			l = lines.get(i);
			String[] parts = l.split(" ");

			if (isCommand(l)) {
				if (parts[2].equals("..")) {
					directoryStack.pop();
					currentDirectory = directoryStack.peek();
				} else {
					for (Directory d : currentDirectory.getChildren()) {
						if (parts[2].equals(d.getName())) {
							currentDirectory = d;
							break;
						}
					}
					directoryStack.push(currentDirectory);
				}
			} else {
				if (parts[0].equals("dir")) {
					parentDir.addChild(new Directory(parts[1], 0, currentDirectory));
				} else {
					fileSize = Integer.parseInt(parts[0]);
					fileName = parts[1];
					parentDir.addChild(new File(fileName, fileSize, currentDirectory));
				}
			}
		}
	}
}
