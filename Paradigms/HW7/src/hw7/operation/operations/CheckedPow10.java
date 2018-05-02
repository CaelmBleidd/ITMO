package hw7.operation.operations;

import hw7.expression.TripleExpression;
import hw7.operation.abstractClasses.UnaryOperation;

public class CheckedPow10 extends UnaryOperation {
    public CheckedPow10(TripleExpression value) {
        super(value);
    }

    @Override
    protected int evaluate(int value) {
        if (value > 9 || value < 0) {
            throw  new ArithmeticException("Overflow expression: pow10 " + value);
        }
        return (int) Math.pow(10, value);
    }
}
