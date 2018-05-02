package hw7.operation.operations;

import hw7.expression.TripleExpression;
import hw7.operation.abstractClasses.BinaryOperation;

public class CheckedMultiply extends BinaryOperation {
    public CheckedMultiply(TripleExpression first, TripleExpression second) {
        super(first, second);
    }

    @Override
    protected int evaluate(int first, int second) {
        if (second > 0 ? first > Integer.MAX_VALUE / second || first < Integer.MIN_VALUE / second
                : (second < -1 ? first > Integer.MIN_VALUE / second || first < Integer.MAX_VALUE / second
                : second == -1 && first == Integer.MIN_VALUE)) {
            throw new ArithmeticException("Overflow expression: " + first + " * " + second);
        }
        return first * second;
    }
}
