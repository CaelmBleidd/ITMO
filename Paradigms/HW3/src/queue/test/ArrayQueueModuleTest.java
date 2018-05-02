package queue.test;

import queue.ArrayQueueModule;

public class ArrayQueueModuleTest {
    public static void main(String[] args) {
        fill();
        dump();
        fill();
        clear();
        fill();
        getArray();

    }

    private static void fill() {
        for (int i = 0; i < 10; i++) {
            ArrayQueueModule.enqueue(i);
        }
    }

    private static void dump() {
        while (!ArrayQueueModule.isEmpty()) {
            System.out.println(ArrayQueueModule.size() + " " + ArrayQueueModule.element() + " " + ArrayQueueModule.dequeue());
        }
    }

    private static void clear() {
        ArrayQueueModule.clear();
        System.out.println("Is queue empty? " + ArrayQueueModule.isEmpty());
    }

    private static void getArray() {
        Object[] newElements = ArrayQueueModule.toArray();
        for (Object newElement : newElements) {
            System.out.print(newElement + " ");
        }
    }
}
