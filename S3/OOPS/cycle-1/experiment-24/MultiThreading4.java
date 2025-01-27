/*
 * Experiment - 24
 * Thread priorities 
 * Athul Anoop
 * 07-10-24
 */

public class MultiThreading4{
	public static void main(String[] args){
		try{
			Thread thread1= new Thread("Thread 1");
			Thread thread2= new Thread("Thread 2");
			System.out.printf("Thread 1 priority: %d\n",thread1.getPriority());
			System.out.printf("Thread 2 priority: %d\n",thread2.getPriority());
			thread1.setPriority(2);
			thread2.setPriority(8);
			System.out.printf("Thread 1 priority: %d\n",thread1.getPriority());
			System.out.printf("Thread 2 priority: %d\n",thread2.getPriority());
	
		} catch (Exception e){
			System.err.println("Some error occurred!");
			e.printStackTrace();
		}
	}
}

