package hw6.operation.abstractClasses;

import hw6.expression.TripleExpression;

public abstract class UnaryOperation implements TripleExpression {
    private TripleExpression value;

    public UnaryOperation(TripleExpression value) {
        this.value = value;
    }

    abstract protected int evaluate(int value);

    @Override
    public int evaluate(int x, int y, int z) {
        return evaluate(value.evaluate(x, y, z));
    }
}
