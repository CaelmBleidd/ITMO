package hw7.operation.abstractClasses;

import hw7.expression.TripleExpression;

public abstract class BinaryOperation implements TripleExpression {
    private TripleExpression first;
    private TripleExpression second;

    public BinaryOperation(TripleExpression first, TripleExpression second) {
        this.first = first;
        this.second = second;
    }

    protected abstract int evaluate(int first, int second);

    @Override
    public int evaluate(int x, int y, int z) {
        return evaluate(first.evaluate(x, y, z), second.evaluate(x, y, z));
    }
}
