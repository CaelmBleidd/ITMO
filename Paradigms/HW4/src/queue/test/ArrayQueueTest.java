package queue.test;

import queue.ArrayQueue;

public class ArrayQueueTest {
    public static void main(String[] args) {
        ArrayQueue arrayQueue = new ArrayQueue();
        fill(arrayQueue);
        dump(arrayQueue);
        fill(arrayQueue);
        clear(arrayQueue);
        fill(arrayQueue);
        getArray(arrayQueue);

    }

    private static void fill(ArrayQueue arrayQueue) {
        for (int i = 0; i < 10; i++) {
            arrayQueue.enqueue(i);
        }
    }

    private static void dump(ArrayQueue arrayQueue) {
        while (!arrayQueue.isEmpty()) {
            System.out.println(arrayQueue.size() + " " + arrayQueue.element() + " " + arrayQueue.dequeue());
        }
    }

    private static void clear(ArrayQueue arrayQueue) {
        arrayQueue.clear();
        System.out.println("Is queue empty? " + arrayQueue.isEmpty());
    }

    private static void getArray(ArrayQueue arrayQueue) {
        Object[] newElements = arrayQueue.toArray();
        for (Object newElement : newElements) {
            System.out.print(newElement + " ");
        }
    }

}
