/*
 * Experiment-19
 * To write a program to show the usage of try, catch, throws and finally.
 * Athul Anoop
 */

import java.util.Scanner;

class InvalidAgeException extends Exception {
	InvalidAgeException(String str){
		super(str);
	}
} 

public class UserDefinedException{
	static Boolean CanVote(int age) throws InvalidAgeException{
		if (age<18){
			throw new InvalidAgeException("Not eligible!");
		} else {
			return true;
		}
	}
	public static void main(String[] args) {
		try {
			Scanner scanner = new Scanner(System.in);
			System.out.println("Age: ");
			Boolean eligible = CanVote(scanner.nextInt());
			if (eligible) {
				System.out.println("You are eligible!");
			}
			scanner.close();
		} catch (InvalidAgeException e){
			System.out.println(e);
		} 
	}
};
