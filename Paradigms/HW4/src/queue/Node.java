package queue;

public class Node {
    protected Object value;
    protected Node next;
    protected Node prev;

    Node(Object value, Node prev, Node next) {
        this.value = value;
        this.next = next;
        this.prev = prev;
    }
}
