package queue;

public class LinkedQueue extends AbstractQueue {
    private Node head;
    private Node tail;

    @Override
    protected void pushRealisation(Object element) {
        head = new Node(element, head, null);
        if (tail == null) {
            tail = head;
        } else {
            head.prev.next = head;
        }
    }

    @Override
    protected Object elementRealisation() {
        return head.value;
    }

    @Override
    protected void dequeueRealisation() {
        if (head.prev != null) {
            head.prev.next = null;
        }
        head = head.prev;
    }

    @Override
    protected void enqueueRealisation(Object element) {
        tail = new Node(element, null, tail);
        if (head == null) {
            head = tail;
        } else {
            tail.next.prev = tail;
        }
    }

    @Override
    protected Object peekRealisation() {
        return tail.value;
    }

    @Override
    protected void removeRealisation() {
        tail = tail.next;
        if (tail != null) {
            tail.prev = null;
        }
    }

}
