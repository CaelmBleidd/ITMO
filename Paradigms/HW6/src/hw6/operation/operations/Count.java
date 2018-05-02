package hw6.operation.operations;

import hw6.expression.TripleExpression;
import hw6.operation.abstractClasses.UnaryOperation;

public class Count extends UnaryOperation {
    public Count(TripleExpression value) {
        super(value);
    }

    @Override
    protected int evaluate(int value) {
        return Integer.bitCount(value);
    }

}
