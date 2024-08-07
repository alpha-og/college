/* 
* Experiment-17
* To write a Java program that reads from a file and write to file 
* by handling all file related exceptions.
* Athul Anoop
* 
*/


import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;
import java.io.IOException;

public class FileExceptions {
	public static void main(String[] args) {
		try {
			File inputFile = new File("input.txt");
			FileWriter outputFileWriter = new FileWriter("output.txt");
			Scanner scanner = new Scanner(inputFile);
			while (scanner.hasNextLine()) {
				String text = scanner.nextLine();
				outputFileWriter.write(text+"\n");
			}
			scanner.close();
			outputFileWriter.close();
		} catch (Exception e) {
			System.out.println("Some error occurred\n" + e);
		}
	
	}
}
