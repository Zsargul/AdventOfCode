import java.util.*;

public class Directory {
	private int size;
	private final String name;
	private final Directory parentDirectory;
	private ArrayList<Directory> childDirectories;
	private ArrayList<File> files;

	// Getters
	public int getSize() {
		int s = this.size;
		for (Directory d : this.getChildren()) {
			s += d.getSize();
		}
		return s;
	}
	public String getName() {
		return this.name;
	}
	public Directory getParent() {
		return this.parentDirectory;
	}
	public ArrayList<Directory> getChildren() {
		return this.childDirectories;
	}
	public ArrayList<File> getFiles() {
		return this.files;
	}

	// Setters
	public void setSize(int size) {
		if (size < 0) throw new IllegalArgumentException("Directory.setSize(): Negative size not allowed.");
		this.size = size;
	}
	public void increaseSize(int size) {
		if (size <= 0) throw new IllegalArgumentException("Directory.increaseSize(): Cannot increase size by 0 or less.");
		this.size = this.getSize() + size;	
	}
	public void addChild(Object child) {
		if ( !(child instanceof Directory) ) throw new IllegalArgumentException("Directory.addChild(): Child object is not of Directory type.");
		if (Objects.isNull(child)) throw new IllegalArgumentException("Directory.addChild(): Child object is null.");
		this.childDirectories.add((Directory)child);	
	}
	public void addFile(Object file) {
		if ( !(file instanceof File) ) throw new IllegalArgumentException("Directory.addFile(): File object is not of File type.");
		if (Objects.isNull(file)) throw new IllegalArgumentException("Directory.addFile(): File object is null.");
		this.files.add((File)file);
		this.increaseSize(((File) file).getSize());
	}

	public void printTree() {
		System.out.println("["+this.getName()+"]\n");
		for (Directory c : this.getChildren()) {
			c.printTree();
		}
		for (File f : this.getFiles()) {
			f.printTree();
		}
	}

	// Constructor
	public Directory(String name, int size, Directory parentDirectory) {
		// Validate variables
		if (name.strip().equals("")) throw new IllegalArgumentException("Directory: Name cannot be empty.");
		if (size != 0) throw new IllegalArgumentException("Directory: Size must be 0 when creating object");
		if (Objects.isNull(parentDirectory) && !name.strip().equals("/")) throw new IllegalArgumentException("Directory: Only the root directory (/) can have no parent");

		this.name = name;
		this.size = size;
		this.parentDirectory = parentDirectory;
		this.childDirectories = new ArrayList<Directory>();
		this.files = new ArrayList<File>();
	}
}
