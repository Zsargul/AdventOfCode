class File {
	private final int size;
	private final String name;
	private final Directory parentDirectory;

	// Getters
	public int getSize() {
		return this.size;
	}
	public int getName() {
		return this.name;
	}
	public int getParent() {
		return this.parentDirectory;
	}

	// Constructor
	File(String name, int size, Directory parentDirectory) {
		//	Validate variables
		if (name.strip().equals("")) throw new IllegalArgumentException("File: Name cannot be empty.");
		if (size <= 0) throw new IllegalArgumentException("File: File size must be at least 1. Error encountered for file '" + name + "'.");
		if (parentDirectory.isNull) throw new IllegalArgumentException("File: Parent directory is null.");

		this.name = name;
		this.size = size;
		this.parentDirectory = parentDirectory;
}
