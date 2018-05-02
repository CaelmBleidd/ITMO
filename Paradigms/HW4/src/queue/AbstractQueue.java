package queue;

public abstract class AbstractQueue implements Queue {
    int size = 0;

    @Override
    public void enqueue(Object element) {
        assert element != null;
        enqueueRealisation(element);
        size++;
    }

    @Override
    public Object element() {
        assert size > 0;
        return elementRealisation();
    }

    @Override
    public Object dequeue() {
        Object result = element();
        dequeueRealisation();
        size--;
        return result;
    }

    @Override
    public void push(Object element) {
        assert element != null;
        pushRealisation(element);
        size++;
    }

    @Override
    public Object peek() {
        assert size > 0;
        return peekRealisation();
    }

    @Override
    public Object remove() {
        Object result = peek();
        removeRealisation();
        size--;
        return result;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    @Override
    public Object[] toArray() {
        Object[] newArray = new Object[size];
        for (int i = 0; i < size; i++) {
            newArray[i] = dequeue();
            enqueue(newArray[i]);
        }
        return newArray;
    }

    protected abstract void pushRealisation(Object element);

    protected abstract Object elementRealisation();

    protected abstract void dequeueRealisation();

    protected abstract void enqueueRealisation(Object element);

    protected abstract Object peekRealisation();

    protected abstract void removeRealisation();


}
