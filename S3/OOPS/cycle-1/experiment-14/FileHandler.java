/* 
* Experiment-14
* To write a file handling program in Java with reader/writer.
* Athul Anoop
* 
*/

import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;


public class FileHandler {
	public static void main(String[] args) {
		try {
			File file = new File("example.txt");
			file.createNewFile();
			FileWriter fileWriter = new FileWriter("example.txt");
			fileWriter.write("Hello world!");
			fileWriter.close();
			Scanner scanner = new Scanner(file);
			String text = scanner.nextLine();
			scanner.close();
			System.out.println(text);

		} catch (Exception e) {
			System.out.println("Some error occurred");
		}
	}
}
