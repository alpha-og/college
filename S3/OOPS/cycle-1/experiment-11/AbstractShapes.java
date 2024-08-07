/* 
* Experiment-11
* To write a Java program to create an abstract class Shape, 
* which contains an empty method numberOfSides()
* To derive 3 classes – Rectangle, Triangle and Hexagon- from Shape, 
* each containing the method numberOfSides().
* Athul Anoop
* 
*/

abstract class Shape {
	public abstract void numberOfSides();
}

class Rectangle extends Shape {
	public void numberOfSides(){
		System.out.println("Rectangle has 4 sides");	
	}
}
class Triangle extends Shape {
	public void numberOfSides(){
		System.out.println("Triangle has 3 sides");	
	}
}

class Hexagon extends Shape {
	public void numberOfSides(){
		System.out.println("Hexagon has 6 sides");	
	}
}

public class AbstractShapes {
	public static void main(String[] args) {
		Rectangle rectangle = new Rectangle();
		rectangle.numberOfSides();
		Triangle triangle = new Triangle();
		triangle.numberOfSides();
		Hexagon hexagon = new Hexagon();
		hexagon.numberOfSides();
	}
} 
