package queue;

public class ArrayQueue extends AbstractQueue {
    private final int startSize = 8;
    private Object elements[];
    private int tail;
    private int head;

    public ArrayQueue() {
        elements = new Object[startSize];
        tail = head = 0;
    }

    private void ensureCapacity(int capacity) {
        if (capacity < elements.length) {
            return;
        }
        Object[] newElements = new Object[capacity << 1];
        newElements = arrayCopy(newElements);
        tail = size;
        head = 0;
        elements = newElements;
    }

    @Override
    protected void pushRealisation(Object element) {
        ensureCapacity(size + 1);
        head = (head == 0) ? elements.length - 1 : head - 1;
        elements[head] = element;
    }

    @Override
    protected Object elementRealisation() {
        return elements[head];
    }

    @Override
    protected void dequeueRealisation() {
        elements[head] = null;
        head = (head + 1) % elements.length;
    }

    @Override
    protected void enqueueRealisation(Object element) {
        ensureCapacity(size + 1);
        elements[tail] = element;
        tail = (tail + 1) % elements.length;
    }

    @Override
    protected Object peekRealisation() {
        return elements[(tail == 0) ? elements.length - 1 : tail - 1];
    }

    @Override
    protected void removeRealisation() {
        tail = (tail == 0) ? elements.length - 1 : tail - 1;
        elements[tail] = null;
    }

    private Object[] arrayCopy(Object[] newElements) {
        int count = (tail < head) ? elements.length - head : size;
        System.arraycopy(elements, head, newElements, 0, count);
        if (tail < head) {
            System.arraycopy(elements, 0, newElements, count, tail);
        }
        return newElements;
    }
}
