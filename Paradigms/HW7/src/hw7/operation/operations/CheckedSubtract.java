package hw7.operation.operations;

import hw7.expression.TripleExpression;
import hw7.operation.abstractClasses.BinaryOperation;

public class CheckedSubtract extends BinaryOperation {
    public CheckedSubtract(TripleExpression first, TripleExpression second) {
        super(first, second);
    }

    @Override
    protected int evaluate(int first, int second) {
        if (second > 0 ? first < Integer.MIN_VALUE + second : first > Integer.MAX_VALUE + second) {
            throw new ArithmeticException("Overflow expression: " + first + " - " + second);
        }
        return first - second;
    }
}
