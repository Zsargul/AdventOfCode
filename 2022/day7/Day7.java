import java.io.*;
import java.util.*;

public class Day7 {
	public static ArrayList<Directory> getDirectories(ArrayList<Directory> dirs, Directory d) {
		dirs.add(d);
		for (Directory c : d.getChildren()) {
			dirs = getDirectories(dirs, c);
		}
		return dirs;
	}

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
			while ((line = reader.readLine()) != null) {
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

		directories.add(new Directory("/", 0, null));
		directoryStack.push(directories.get(0));
		Directory currentDirectory;

		for (int i = 1; i < lines.size(); i++) {
			currentDirectory = directoryStack.peek();
			l = lines.get(i);
			String[] parts = l.split(" ");

			if (isCommand(l)) {
				if (parts[2].equals("..")) {
					directoryStack.pop();
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
					currentDirectory.addChild(new Directory(parts[1], 0, currentDirectory));
				} else {
					fileSize = Integer.parseInt(parts[0]);
					fileName = parts[1];
					currentDirectory.addFile(new File(fileName, fileSize, currentDirectory));
				}
			}
		}

		ArrayList<Directory> dirs = new ArrayList<Directory>();
		int sum = 0;
		if (!directories.get(0).getName().equals("/")) {
			throw new RuntimeException("Error: Root directory ('/') is not at the start of directories ArrayList!");
		} else {
			dirs = getDirectories(dirs, directories.get(0));
			for (Directory d : dirs) {
				if (d.getSize() <= 100000) {
					sum += d.getSize();
				}
			}
		}
		System.out.println(sum); // Part 1
								 
		int totalSpace = 70000000;
		int spaceNeededForUpdate = 30000000;

		int freeSpace = totalSpace - directories.get(0).getSize();
		int neededFreeSpace = spaceNeededForUpdate - freeSpace;

		Directory toDelete = dirs.get(0);
		for (Directory d : dirs) {
			if (d.getSize() < neededFreeSpace) continue;
			
			if (d.getSize() < toDelete.getSize()) toDelete = d;
		}
		System.out.println(toDelete.getSize());

	}
}
