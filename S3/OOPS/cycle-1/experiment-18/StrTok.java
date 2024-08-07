/*
 * Experiment-18
 * To write a Java program that reads a line of integers, and then displays each integer, and the sum of all the integers (Use String Tokenizer class of java.util).
 * Athul Anoop
 */

import java.util.Scanner;
import java.util.StringTokenizer;

public class StrTok {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		String input = scanner.nextLine();
		StringTokenizer tokens = new StringTokenizer(input);
		int sum = 0;
		while (tokens.hasMoreTokens()) {
			String token = tokens.nextToken();
			System.out.printf("%s ",token);
			sum += Integer.parseInt(token);
		}
		System.out.printf("\nSum: %s ",sum);
	}
}
