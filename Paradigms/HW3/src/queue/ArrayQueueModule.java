package queue;

public class ArrayQueueModule {
    private static final int startSize = 8;
    private static Object elements[];
    private static int tail;
    private static int head;
    private static int size;

    public ArrayQueueModule() {
        elements = new Object[startSize];
        tail = head = size = 0;
    }


    public static void enqueue(Object element) {
        assert element != null;
        ensureCapacity(size + 1);
        elements[tail] = element;
        tail = (tail + 1) % elements.length;
        size++;
    }

    private static void ensureCapacity(int capacity) {
        if (capacity < elements.length) {
            return;
        }
        Object[] newElements = new Object[capacity * 2];
        newElements = arrayCopy(newElements);
        tail = size;
        head = 0;
        elements = newElements;
    }

    public static Object element() {
        assert size > 0;
        return elements[head];
    }

    public static Object dequeue() {
        assert size > 0;
        Object result = element();
        elements[head] = null;
        head = (++head) % elements.length;
        size--;
        return result;

    }

    public static int size() {
        return size;
    }

    public static boolean isEmpty() {
        return size == 0;
    }

    public static void push(Object element) {
        assert element != null;
        ensureCapacity(size + 1);
        head = (head == 0) ? elements.length - 1 : head - 1;
        elements[head] = element;
        size++;
    }

    public static Object peek() {
        assert size > 0;
        return elements[(tail == 0) ? elements.length - 1 : tail - 1];
    }

    public static Object remove() {
        assert size > 0;
        Object result = peek();
        tail = (tail != 0) ? tail - 1 : elements.length - 1;
        elements[tail] = null;
        size--;
        return result;

    }

    public static void clear() {
        head = tail = size = 0;
        elements = new Object[startSize];
    }

    public static Object[] toArray() {
        Object[] newElements = new Object[size];
        newElements = arrayCopy(newElements);
        return newElements;
    }

    public static Object[] arrayCopy(Object[] newElements) {
        int count = (tail < head) ? elements.length - head : size;
        System.arraycopy(elements, head, newElements, 0, count);
        if (tail < head) {
            System.arraycopy(elements, 0, newElements, count, tail);
        }
        return newElements;
    }
}
