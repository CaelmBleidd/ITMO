package hw6.operation.operations;

import hw6.expression.TripleExpression;
import hw6.operation.abstractClasses.UnaryOperation;

public class UnaryMinus extends UnaryOperation {
    public UnaryMinus(TripleExpression value) {
        super(value);
    }

    @Override
    protected int evaluate(int value) {
        return -value;
    }
}
