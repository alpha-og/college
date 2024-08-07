/* 
* Experiment-13
* To write a Java program to demonstrate garbage collection.
* Athul Anoop
* 
*/

class Car {
	String brand;
	Car(String brand){
		this.brand = brand;
	}
	public void display(){
		System.out.println(this.brand);
	}
}

public class Garbage{
	public static void main(String args[]){
		Car car1 = new Car("Rivian");
		Car car2 = new Car("Porsche");
		System.out.println("Before reference is left dangling");
		car1.display();
		car2.display();
		car1 = car2;
		System.out.println("After reference is left dangling");
		car1.display();
		car2.display();
	}
}
