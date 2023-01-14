import java.io.*;
import java.util.*;

class Day6 {
	public static void main(String args[]) {
		char r = '';
		try {
			BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
			
			int c = 0;
			boolean fourPushed = false;
			LinkedList<Character> chars = new LinkedList<Character>();
			while ((r = reader.read()) != -1) {
				chars.add(r);
				c++;

				if (fourPushed) {
					// Check for duplicates here
				} else {
					if (chars.size() == 3) {
						fourPushed = true;
					}
				}
			}
		} catch (IOException ex) {
			throw new RuntimeException(ex);
		}
	}
}
