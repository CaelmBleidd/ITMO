package queue.test;

import queue.ArrayQueueADT;

public class ArrayQueueADTTest {
    public static void main(String[] args) {
        ArrayQueueADT arrayQueueADT = new ArrayQueueADT();
        fill(arrayQueueADT);
        dump(arrayQueueADT);
        fill(arrayQueueADT);
        clear(arrayQueueADT);
        fill(arrayQueueADT);
        getArray(arrayQueueADT);

    }

    private static void fill(ArrayQueueADT arrayQueueADT) {
        for (int i = 0; i < 10; i++) {
            ArrayQueueADT.enqueue(arrayQueueADT, i);
        }
    }

    private static void dump(ArrayQueueADT arrayQueueADT) {
        while (!ArrayQueueADT.isEmpty(arrayQueueADT)) {
            System.out.println(ArrayQueueADT.size(arrayQueueADT) + " " + ArrayQueueADT.element(arrayQueueADT) + " " + ArrayQueueADT.dequeue(arrayQueueADT));
        }
    }

    private static void clear(ArrayQueueADT arrayQueueADT) {
        ArrayQueueADT.clear(arrayQueueADT);
        System.out.println("Is queue empty? " + ArrayQueueADT.isEmpty(arrayQueueADT));
    }

    private static void getArray(ArrayQueueADT arrayQueueADT) {
        Object[] newElements = ArrayQueueADT.toArray(arrayQueueADT);
        for (Object newElement : newElements) {
            System.out.print(newElement + " ");
        }
    }
}
