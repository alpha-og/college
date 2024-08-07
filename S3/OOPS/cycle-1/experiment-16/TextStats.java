/* 
* Experiment-16
* To write a Java program that displays the number of characters, words, and lines in a text file.
* Athul Anoop
* 
*/


import java.io.File;
import java.util.Scanner;

public class TextStats {
	public static void main(String[] args) {
		try {
			File file = new File("example.txt");
			Scanner scanner = new Scanner(file);
			int characterCount = 0;
			int wordCount = 0;
			int lineCount = 0;
			while (scanner.hasNextLine()) {
				String line = scanner.nextLine();
				String words[] = line.split(" ");
				wordCount += words.length;
				for (String word: words){
					characterCount += word.length();
				}
				lineCount++;
			}
			scanner.close();
			System.out.printf("Lines: %d | Words: %d | Characters: %d",lineCount, wordCount, characterCount);
		} catch (Exception e) {
			System.out.println("Some error occurred" + e);
		}
	
	}
}
