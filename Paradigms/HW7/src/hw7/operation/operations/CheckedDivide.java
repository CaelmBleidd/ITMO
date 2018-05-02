package hw7.operation.operations;

import hw7.expression.TripleExpression;
import hw7.operation.abstractClasses.BinaryOperation;

public class CheckedDivide extends BinaryOperation {
    public CheckedDivide(TripleExpression first, TripleExpression second) {
        super(first, second);
    }

    @Override
    protected int evaluate(int first, int second) {
        if (first == Integer.MIN_VALUE && second == -1) {
            throw new ArithmeticException("Overflow expression: " + first + " / " + second);
        }
        if (second == 0) {
            throw new ArithmeticException("Division by zero: " + first + " / " + second);
        }
        return first / second;
    }
}
