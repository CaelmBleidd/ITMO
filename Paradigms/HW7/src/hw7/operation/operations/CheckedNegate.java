package hw7.operation.operations;

import hw7.expression.TripleExpression;
import hw7.operation.abstractClasses.UnaryOperation;

public class CheckedNegate extends UnaryOperation {
    public CheckedNegate(TripleExpression value) {
        super(value);
    }

    @Override
    protected int evaluate(int value) {
        if (value == Integer.MIN_VALUE) {
            throw new ArithmeticException("Overflow expression: -" + value);
        }
        return -value;
    }
}
