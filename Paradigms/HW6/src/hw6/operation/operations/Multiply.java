package hw6.operation.operations;

import hw6.expression.TripleExpression;
import hw6.operation.abstractClasses.BinaryOperation;

public class Multiply extends BinaryOperation {
    public Multiply(TripleExpression first, TripleExpression second) {
        super(first, second);
    }

    @Override
    protected int evaluate(int first, int second) {
        return first * second;
    }
}
