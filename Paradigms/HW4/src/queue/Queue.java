package queue;

public interface Queue {
    // Pre: value != null
    // Post: queue[tail - 1] = element
    // Post: size' = size + 1
    void enqueue(Object element);

    // Pre: size > 0
    // Post: Result = queue[head]
    Object element();

    //Pre: size > 0
    //Post: result = queue[head] && size' = size - 1
    Object dequeue();

    // Pre: size > 0
    // Post: Result = queue[tail - 1]
    Object peek();

    // Pre: element != null
    // Post: queue[head] = element
    // Post: size' = size + 1
    void push(Object element);

    // Pre: size > 0
    // Post: Result = queue[tail - 1]
    // Post: size' = size - 1
    Object remove();

    //Post: Result = size
    int size();

    //Post: Result = (size == 0 ?)
    boolean isEmpty();

    // Inv: size' = 0;
    // Post: Clear the queue
    void clear();

    // Post: Result = queue[0..size - 1]
    Object toArray();
}
