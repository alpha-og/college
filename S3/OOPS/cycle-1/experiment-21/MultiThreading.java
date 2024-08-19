/*
 * Experiment - 21
 * Write a Java program that implements a multi-threaded program which has three threads. 
 * First thread generates a random integer every 1 second. If the value is even, second 
 * thread computes the square of the number and prints. If the value is odd the third 
 * thread will print the value of cube of the number.
 * Athul Anoop
 */

import java.util.concurrent.ThreadLocalRandom;
public class MultiThreading {
    static int rand;
    static synchronized void generateRandomNumber(){
        rand = ThreadLocalRandom.current().nextInt(100);
    }
    static synchronized void square(){
        System.out.printf("Random Number: %d | Square: %f\n", rand, Math.pow(rand, 2));
    }
    static synchronized void cube(){
        System.out.printf("Random Number: %d | Cube: %f\n", rand, Math.pow(rand, 3));
    }
    public static void main(String[] args) {
        while(true){
            try{
                Thread threadRng = new Thread(()->{
                    generateRandomNumber();
                });
                Thread threadSquare = new Thread(()->{
                    square();
                });
                Thread threadCube = new Thread(()->{
                    cube();
                });

                    threadRng.start();
                    if (rand%2==0) threadSquare.start();
                    else threadCube.start();;
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }
}
