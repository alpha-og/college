/* 
* Experiment-12
* To write a Java program to demonstrate the concept of interface inheritance.
* Athul Anoop
* 
*/
enum Category {
	HEAVY,
	MEDIUM,
	LIGHT
}

interface Vehicle {
	public Category get_category();
	public String get_brand();
}

class Car implements Vehicle{
	Category category;
	String brand;
	Car(Category category, String brand){
		this.category = category;
		this.brand = brand;
	}
	public Category get_category(){
		return this.category;
	}
	public String get_brand(){
		return this.brand;
	}
}

public class Interfaces {
	public static void main(String args[]){
		Car car = new Car(Category.HEAVY, "Lucid");
		System.out.printf("Brand: %s | Category: %s",car.get_brand(),car.get_category());
	}
}
