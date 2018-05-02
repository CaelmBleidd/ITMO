package queue.test;

import queue.ArrayQueueD;
import queue.ArrayQueue;

public class PetooohTest {
    private static final long start = System.currentTimeMillis();

    public static void main(String[] args) {
        ArrayQueueD queueDanya = new ArrayQueueD();
        ArrayQueue queue = new ArrayQueue();

        System.out.println("Начал выполнение.");
        System.err.println("===========================================");

        fillBigArray(queue);
        System.err.format("A: Done fillBigArray. Finished in %d ms%n", System.currentTimeMillis() - start);
        System.err.println("===========================================");

        dump(queue);
        System.err.format("A: Clear array. Finished in %d ms%n", System.currentTimeMillis() - start);
        System.err.println("===========================================");
//
//        dump(queueDanya);
//        System.err.format("D: Clear array. Finished in %d ms%n", System.currentTimeMillis() - start);
//        System.err.println("===========================================");

        cycleFill(queue);
        System.err.format("A: Done cycle. Finished in %d ms%n", System.currentTimeMillis() - start);
        System.err.println("===========================================");

        clear(queue);
        System.err.format("A: Clear array by clear(). Finished in %d ms%n", System.currentTimeMillis() - start);
        System.err.println("===========================================");
//
//        cycleFill(queueDanya);
//        System.err.format("D: Done cycle. Finished in %d ms%n", System.currentTimeMillis() - start);
//        System.err.println("===========================================");
//
//        clear(queueDanya);
//        System.err.format("D: Clear array by clear(). Finished in %d ms%n", System.currentTimeMillis() - start);
//        System.err.println("===========================================");

        veryBigArray(queue);
        System.err.format("A: Checked memory. Finished in %d ms%n", System.currentTimeMillis() - start);
        System.err.println("===========================================");

        clear(queue);
        System.err.format("A: Clear array by clear(). Finished in %d ms%n", System.currentTimeMillis() - start);
        System.err.println("===========================================");

//        veryBigArray(queueDanya);
//        System.err.format("D: Checked memory. Finished in %d ms%n", System.currentTimeMillis() - start);
//        System.err.println("===========================================");
//
//        clear(queueDanya);
//        System.err.format("D: Clear array by clear(). Finished in %d ms%n", System.currentTimeMillis() - start);
//        System.err.println("===========================================");

        System.err.format("Total finished in %d ms%n", System.currentTimeMillis() - start);
    }

    public static void fillBigArray(ArrayQueueD queueDanya) {
        for (int i = 0; i < 1e8; i++) {
            queueDanya.enqueue(i);
        }
    }

    public static void clear(ArrayQueueD queueDanya) {
        queueDanya.clear();
    }

    public static void dump(ArrayQueueD queueDanya) {
        while (!queueDanya.isEmpty()) {
            queueDanya.dequeue();
        }
    }

    public static void cycleFill(ArrayQueueD queueDanya) {
        for (int i = 0; i < 1e8; i++) {
            for (int j = 0; j < 127; j++) {
                queueDanya.enqueue(i);
            }
            dump(queueDanya);
        }
    }

    public static void veryBigArray(ArrayQueueD queueDanya) {
        for (int i = 0; i < 100400000; i++) {
            queueDanya.enqueue(i);
        }
    }

    public static void veryBigArray(ArrayQueue queue) {
        for (int i = 0; i < 100400000; i++) {
            queue.enqueue(i);
        }
    }

    public static void fillBigArray(ArrayQueue queue) {
        for (int i = 0; i < 1e8; i++) {
            queue.enqueue(i);
        }
    }

    public static void clear(ArrayQueue queue) {
        queue.clear();
    }

    public static void dump(ArrayQueue queue) {
        while (!queue.isEmpty()) {
            queue.dequeue();
        }
    }

    public static void cycleFill(ArrayQueue queue) {
        for (int i = 0; i < 1e8; i++) {
            for (int j = 0; j < 127; j++) {
                queue.enqueue(i);
            }
            dump(queue);
        }
    }
}
