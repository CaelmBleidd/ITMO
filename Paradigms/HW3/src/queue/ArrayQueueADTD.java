package queue;

public class ArrayQueueADTD<T> {
    static private int DEFAULT_SIZE = 8;
    private Object[] array = new Object[DEFAULT_SIZE];
    private int first = 0;
    private int size = 0;

    public static <T> void enqueue(ArrayQueueADTD<T> queue, T element) {
        if (queue.size + 1 > queue.array.length) {
            Object[] t = new Object[queue.array.length * 2];
            System.arraycopy(queue.array, queue.first, t, queue.array.length + queue.first, queue.array.length - queue.first);
            System.arraycopy(queue.array, 0, t, 0, queue.size - (queue.array.length - queue.first));
            queue.first += queue.array.length;
            queue.array = t;
        }

        queue.array[(queue.first + queue.size) % queue.array.length] = element;
        queue.size++;
    }

    public static <T> T element(ArrayQueueADTD<T> queue) {
        return (T) queue.array[queue.first];
    }

    public static <T> T dequeue(ArrayQueueADTD<T> queue) {
        assert queue.size > 0;
        queue.size--;
        int lastValue = queue.first;
        queue.first = (queue.first + 1) % queue.array.length;
        return (T) queue.array[lastValue];
    }

    public static <T> int size(ArrayQueueADTD<T> queue) {
        return queue.size;
    }

    public static <T> boolean isEmpty(ArrayQueueADTD<T> queue) {
        return queue.size == 0;
    }

    public static <T> void clear(ArrayQueueADTD<T> queue) {
        queue.array = new Object[DEFAULT_SIZE];
        queue.first = 0;
        queue.size = 0;
    }

    public static <T> T[] toArray(ArrayQueueADTD<T> queue) {
        Object[] newArray = new Object[queue.size];
        System.arraycopy(queue.array, queue.first, newArray, 0, queue.size);
        return (T[]) newArray;
    }

}
