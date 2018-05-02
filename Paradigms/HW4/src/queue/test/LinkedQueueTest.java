package queue.test;

import queue.LinkedQueue;

public class LinkedQueueTest {
    public static void main(String[] args) {
        LinkedQueue LinkedQueue = new LinkedQueue();
        fill(LinkedQueue);
        dump(LinkedQueue);
        fill(LinkedQueue);
        clear(LinkedQueue);
        fill(LinkedQueue);
        getArray(LinkedQueue);

    }

    private static void fill(LinkedQueue LinkedQueue) {
        for (int i = 0; i < 10; i++) {
            LinkedQueue.enqueue(i);
        }
    }

    private static void dump(LinkedQueue LinkedQueue) {
        while (!LinkedQueue.isEmpty()) {
            System.out.println(LinkedQueue.size() + " " + LinkedQueue.element() + " " + LinkedQueue.dequeue());
        }
    }

    private static void clear(LinkedQueue LinkedQueue) {
        LinkedQueue.clear();
        System.out.println("Is queue empty? " + LinkedQueue.isEmpty());
    }

    private static void getArray(LinkedQueue LinkedQueue) {
        Object[] newElements = LinkedQueue.toArray();
        for (Object newElement : newElements) {
            System.out.print(newElement + " ");
        }
    }
}
