package hw7.operation.operations;

import hw7.expression.TripleExpression;
import hw7.operation.abstractClasses.UnaryOperation;

public class CheckedLog10 extends UnaryOperation {
    public CheckedLog10(TripleExpression value) {
        super(value);
    }

    @Override
    protected int evaluate(int value) {
        if (value <= 0) {
            throw new ArithmeticException("Log of not positive value: " + value);
        }
        return (int) Math.log10(value);
    }
}
