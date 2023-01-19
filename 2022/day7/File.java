import java.util.*;

public class File {
	private final int size;
	private final String name;
	private final Directory parentDirectory;

	// Getters
	public int getSize() {
		return this.size;
	}
	public String getName() {
		return this.name;
	}
	public Directory getParent() {
		return this.parentDirectory;
	}

	public void printTree() {
		System.out.println("["+this.getName()+"]-["+this.getSize()+"]"); 
	}

	// Constructor
	public File(String name, int size, Directory parentDirectory) {
		//	Validate variables
		if (name.strip().equals("")) throw new IllegalArgumentException("File: Name cannot be empty.");
		if (size <= 0) throw new IllegalArgumentException("File: File size must be at least 1. Error encountered for file '" + name + "'.");
		if (Objects.isNull(parentDirectory)) throw new IllegalArgumentException("File: Parent directory is null.");

		this.name = name;
		this.size = size;
		this.parentDirectory = parentDirectory;
	}
}
