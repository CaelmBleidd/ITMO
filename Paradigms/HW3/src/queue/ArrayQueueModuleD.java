package queue;

public class ArrayQueueModuleD {
    static private int DEFAULT_SIZE = 8;
    static private Object[] array = new Object[DEFAULT_SIZE];
    static private int first = 0;
    static private int size = 0;

    public static void enqueue(Object element) {

        if (size + 1 > array.length) {
            Object[] t = new Object[array.length * 2];
            System.arraycopy(array, first, t, array.length + first, array.length - first);
            System.arraycopy(array, 0, t, 0, size - (array.length - first));
            first += array.length;
            array = t;
        }

        array[(first + size) % array.length] = element;
        size++;
    }

    public static Object element() {
        return array[first];
    }

    public static Object dequeue() {
        assert size > 0;
        size--;
        int lastValue = first;
        first = (first + 1) % array.length;
        return array[lastValue];
    }

    public static int size() {
        return size;
    }

    public static boolean isEmpty() {
        return size == 0;
    }

    public static void clear() {
        array = new Object[DEFAULT_SIZE];
        first = 0;
        size = 0;
    }

    public static Object[] toArray() {
        Object[] t = new Object[size];
        return t;
    }
}
