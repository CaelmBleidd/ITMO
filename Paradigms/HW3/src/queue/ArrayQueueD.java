package queue;

public class ArrayQueueD<T> {
    static private int DEFAULT_SIZE = 8;
    private Object[] array = new Object[DEFAULT_SIZE];
    private int first = 0;
    private int size = 0;

    private Object[] nextArray;
    private int startWith = -1;
    private int step = Integer.MAX_VALUE;
    private int i = Integer.MIN_VALUE;

    public Object[] getNextArray() {
        return nextArray;
    }

    public Object[] getArray() {
        return array;
    }

    public int getFirst() {
        return first;
    }

    public void enqueue(T element) {
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

    public T element() {
        return (T) array[first];
    }

    public T dequeue() {
        assert size > 0;
        size--;
        int lastValue = first;
        first = (first + 1) % array.length;
        return (T) array[lastValue];
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public void clear() {
        array = new Object[DEFAULT_SIZE];
        first = 0;
        size = 0;
    }

    public Object[] toArray() {
        Object[] newArray = new Object[size];
        System.arraycopy(array, first, newArray, 0, size);
        return newArray;
    }

}
