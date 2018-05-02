package queue;

public class ArrayQueue {
    private final int startSize = 8;
    private Object elements[];
    private int tail;
    private int head;
    private int size;


    public ArrayQueue() {
        elements = new Object[startSize];
        tail = head = size = 0;
    }

    // Pre: value != null
    // Post: queue[tail - 1] = element
    // Post: size' = size + 1
    public void enqueue(Object element) {
        assert element != null;
        ensureCapacity(size + 1);
        elements[tail] = element;
        tail = (tail + 1) % elements.length;
        size++;
    }

    // Pre: capacity' > 0
    // Post: if required capacity of array bigger then current, capacity' = capacity * 2
    // Inv: if (capacity' = capacity * 2) head < tail
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

    // Pre: size > 0
    // Post: Result = queue[head]
    public Object element() {
        assert size > 0;
        return elements[head];
    }

    //Pre: size > 0
    //Post: result = queue[head] && size' = size - 1
    public Object dequeue() {
        assert size > 0;
        Object result = element();
        elements[head] = null;
        head = (head + 1) % elements.length;
        size--;
        return result;

    }

    //Post: Result = size
    public int size() {
        return size;
    }

    //Post: Result = (size == 0 ?)
    public boolean isEmpty() {
        return size == 0;
    }

    // Pre: element != null
    // Post: queue[head] = element
    // Post: size' = size + 1
    public void push(Object element) {
        assert element != null;
        ensureCapacity(size + 1);
        head = (head == 0) ? elements.length - 1 : head - 1;
        elements[head] = element;
        size++;
    }

    // Pre: size > 0
    // Post: Result = queue[tail - 1]
    public Object peek() {
        assert size > 0;
        return elements[(tail == 0) ? elements.length - 1 : tail - 1];
    }

    // Pre: size > 0
    // Post: Result = queue[tail - 1]
    // Post: size' = size - 1
    public Object remove() {
        assert size > 0;
        Object result = peek();
        tail = (tail == 0) ? elements.length - 1 : tail - 1;
        elements[tail] = null;
        size--;
        return result;

    }

    // Inv: size' = 0;
    // Post: Clear the queue
    public void clear() {
        head = tail = size = 0;
        elements = new Object[startSize];
    }

    // Post: Result = queue[0..size - 1]
    public Object[] toArray() {
        Object[] newElements = new Object[size];
        newElements = arrayCopy(newElements);
        return newElements;
    }

    public Object[] arrayCopy(Object[] newElements) {
        int count = (tail < head) ? elements.length - head : size;
        System.arraycopy(elements, head, newElements, 0, count);
        if (tail < head) {
            System.arraycopy(elements, 0, newElements, count, tail);
        }
        return newElements;
    }
}
