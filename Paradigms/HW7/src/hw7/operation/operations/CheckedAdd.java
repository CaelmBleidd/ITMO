package hw7.operation.operations;

import hw7.exceptions.ArithmeticParserException;
import hw7.expression.TripleExpression;
import hw7.operation.abstractClasses.*;

public class CheckedAdd extends BinaryOperation {
    public CheckedAdd(TripleExpression first, TripleExpression second) {
        super(first, second);
    }

    @Override
    protected int evaluate(int first, int second) {
        if (second > 0 ? Integer.MAX_VALUE - second < first : Integer.MIN_VALUE - second > first) {
            throw new ArithmeticParserException("Overflow exception : " + first + " + " + second);
        }
        return first + second;
    }

}
