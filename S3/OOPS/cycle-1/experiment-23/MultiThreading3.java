/*
 * Experiment - 23
 * Using two threads to display odd and even numbers respectively
 * Athul Anoop
 * 26-09-24
 */

public class MultiThreading3{
	public static void main(String[] args){
		try{
			Thread threadOdd= new Thread(()->{
				for (int i=1; i< 100; i++){
					if (i%2 == 1){
						System.out.println("Odd: "+i);
					}
				}
			});
			Thread threadEven = new Thread(()->{
				for (int i=1; i< 100; i++){
					if (i%2 == 0){
						System.out.println("Even: "+i);
					}
				}
			});
			threadOdd.start();
			threadEven.start();
		} catch (Exception e){
			System.err.println("Some error occurred!");
			e.printStackTrace();
		}
	}
}
