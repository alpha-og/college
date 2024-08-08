/*
 * Experiment-19
 * To write a program to show the usage of try, catch, throws and finally.
 * Athul Anoop
 */

import java.util.Scanner;
import java.io.File;
import java.io.IOException;

public class ErrorHandling{
	public static void main(String[] args) {
		Scanner scanner; 
		File user;
		try {
			scanner = new Scanner(System.in);
			System.out.print("Username: ");
			String username = scanner.nextLine();
			System.out.print("Password: ");
			String password = scanner.nextLine();
			if (username=="" || password=="") {
				throw new Exception("Username and password are required");
			}
			user = new File("user.csv");
			scanner = new Scanner(user);
			String userDetails[] = scanner.nextLine().split(",");
			if (!(username.equals(userDetails[0]) && password.equals(userDetails[1]))){
				throw new SecurityException();
			}
			scanner.close();
			System.out.println("Sign In successful");

		} catch (IOException e) {
			System.out.println("Error: Unable read/ access user.csv");
			e.printStackTrace();
		} catch (SecurityException e) {
			System.out.println("Error: Username or Password is incorrect!");
			e.printStackTrace();
		} catch (Exception e){
			System.out.println("Error: Unhandled exception!");
		}finally {
			System.out.println("Exiting...");
		} 
	}
};
