package queue;

public class ArrayQueueADT {
    private static final int startSize = 8;
    private Object elements[];
    private int tail;
    private int head;
    private int size;

    public ArrayQueueADT() {
        elements = new Object[startSize];
        tail = head = size = 0;
    }


    public static void enqueue(ArrayQueueADT adt, Object element) {
        assert element != null;
        ensureCapacity(adt, adt.size + 1);
        adt.elements[adt.tail] = element;
        adt.tail = (adt.tail + 1) % adt.elements.length;
        adt.size++;
    }

    private static void ensureCapacity(ArrayQueueADT adt, int capacity) {
        if (capacity < adt.elements.length) {
            return;
        }
        Object[] newElements = new Object[adt.elements.length << 1];
        int count = adt.tail < adt.head ? adt.elements.length - adt.head : adt.size;
        System.arraycopy(adt.elements, adt.head, newElements, 0, count);
        if (adt.tail < adt.head) {
            System.arraycopy(adt.elements, 0, newElements, count, adt.tail);
        }
        adt.tail = adt.size;
        adt.head = 0;
        adt.elements = newElements;
    }

    public static Object element(ArrayQueueADT adt) {
        assert adt.size > 0;
        return adt.elements[adt.head];
    }

    public static Object dequeue(ArrayQueueADT adt) {
        assert adt.size > 0;
        Object result = element(adt);
        adt.elements[adt.head] = null;
        adt.head = (adt.head + 1) % adt.elements.length;
        adt.size--;
        return result;

    }

    public static int size(ArrayQueueADT adt) {
        return adt.size;
    }

    public static boolean isEmpty(ArrayQueueADT adt) {
        return adt.size == 0;
    }

    public static void push(ArrayQueueADT adt, Object element) {
        assert element != null;
        ensureCapacity(adt, adt.size + 1);
        adt.head = (adt.head == 0) ? adt.elements.length - 1 : adt.head - 1;
        adt.elements[adt.head] = element;
        adt.size++;
    }

    public static Object peek(ArrayQueueADT adt) {
        assert adt.size > 0;
        return adt.elements[(adt.tail == 0) ? adt.elements.length - 1 : adt.tail - 1];
    }

    public static Object remove(ArrayQueueADT adt) {
        assert adt.size > 0;
        Object result = peek(adt);
        adt.tail = (adt.tail == 0) ? adt.elements.length - 1 : adt.tail - 1;
        adt.elements[adt.tail] = null;
        adt.size--;
        return result;

    }

    public static void clear(ArrayQueueADT adt) {
        adt.head = adt.tail = adt.size = 0;
        adt.elements = new Object[startSize];
    }

    public static Object[] toArray(ArrayQueueADT adt) {
        Object[] newElements = new Object[adt.size];
        int count = (adt.tail < adt.head) ? adt.elements.length - adt.head : adt.size;
        System.arraycopy(adt.elements, adt.head, newElements, 0, count);
        if (adt.tail < adt.head) {
            System.arraycopy(adt.elements, 0, newElements, count, adt.tail);
        }
        return newElements;
    }
}
