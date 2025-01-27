/*
 * Experiment - 22
 * Illustrating synchronized threads 
 * Athul Anoop
 * 29-08-24
 */

public class MultiThreading2{
	static int count;
public static void main(String[] args){
	for(int i = 0; i < 10; i++){
		try{
			Thread threadIncrement1 = new Thread(()->{
			count ++;
			});
			Thread threadIncrement2 = new Thread(()-> {
				count ++;
			});
			threadIncrement1.start();
			threadIncrement2.start();
			threadIncrement1.join();
			threadIncrement2.join();
	
		} catch (Exception e){
			System.err.println("Some error occurred!");
			e.printStackTrace();
		}
	}
			System.out.println("Count:  "+ count);
	}
}
