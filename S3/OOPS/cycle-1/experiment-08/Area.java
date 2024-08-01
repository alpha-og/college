/*
 * Experiment - 08
 * To implement a Java program to calculate the area of circle, rectangle and triangle.
 * Athul Anoop
 */

import java.util.Scanner;

class Circle {
	double radius;
	Circle(double radius){
		this.radius = radius;
	}
	public double calculateArea(){
		return Math.PI * Math.pow(this.radius, 2);
	}
}

class Rectangle {
	double length;
	double breadth;
	Rectangle(double length, double breadth){
		this.length = length;
		this.breadth = breadth;
	};
	public double calculateArea(){
		return this.length * this.breadth;
	}
}

class Triangle {
	double sideA;
	double sideB;
	double sideC;
	Triangle(double sideA, double sideB, double sideC){
		this.sideA = sideA;
		this.sideB = sideB;
		this.sideC = sideC;
	}
	public double calculateArea(){
		double semiPerimeter = (sideA + sideB + sideC)/2; 
		return Math.sqrt(semiPerimeter*(semiPerimeter-sideA)*(semiPerimeter-sideB)*(semiPerimeter-sideC));
	}
}

public class Area {
	public static void displayMenu(){
		System.out.println("\n---- Area Calculator ----");
		System.out.println("1. Circle");
		System.out.println("2. Rectangle");
		System.out.println("3. Triangle");
		System.out.println("4. Exit");
		System.out.println("Choose an option (1-4): ");
	}
	public static void handleChoice(){
		Scanner scanner = new Scanner(System.in);
		int choice = scanner.nextInt();
		double area;
		switch (choice) {
			case 1:
				System.out.println("\n---- Circle ----");
				System.out.print("Radius of circle: ");
				double radius = scanner.nextDouble();
				Circle circle = new Circle(radius);
				area = circle.calculateArea();
				System.out.printf("Area of circle is %f squared units", area);
				break;
			case 2:
				System.out.println("\n---- Rectangle ----");
				System.out.print("Dimensions of rectangle (length breadth): ");
				double length = scanner.nextDouble();
				double breadth = scanner.nextDouble();
				Rectangle rectangle = new Rectangle(length, breadth);
				area = rectangle.calculateArea();
				System.out.printf("Area of rectangle is %f squared units", area);
				break;
			case 3:
				System.out.println("\n---- Triangle ----");
				System.out.print("Sides of triangle(a b c): ");
				double sideA = scanner.nextDouble();
				double sideB = scanner.nextDouble();
				double sideC = scanner.nextDouble();
				Triangle triangle = new Triangle(sideA, sideB, sideC);
				area = triangle.calculateArea();
				System.out.printf("Area of triangle is %f squared units", area);
				break;
			case 4:
				System.exit(0);
				break;
			default:
				System.out.println("\nInvalid choice! Try again...");
				break;
		}
	}
	public static void main(String args[]){
		while (true){
			displayMenu();
			handleChoice();
		}
	}
}
