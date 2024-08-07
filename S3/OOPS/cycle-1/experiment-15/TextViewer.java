/* 
* Experiment-15
* To write a Java program that reads a file and displays the file on the screen,
* with a line number before each line.
* Athul Anoop
* 
*/


import java.io.File;
import java.util.Scanner;

public class TextViewer {
	public static void main(String[] args) {
		try {
			File file = new File("example.txt");
			Scanner scanner = new Scanner(file);
			String text;
			int lineNumber = 0;
			while (scanner.hasNextLine()) {
				System.out.println(lineNumber + ". "+scanner.nextLine());
				lineNumber++;
			}
		} catch (Exception e) {
			System.out.println("Some error occurred" + e);
		}
	
	}
}
