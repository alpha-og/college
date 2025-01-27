/*
 * Experiment - 21
 * Multi-threaded program which has three threads.
 * Athul Anoop
 * 29-08-24
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
