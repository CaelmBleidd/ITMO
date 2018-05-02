package hw6.operation.operations;

import hw6.expression.TripleExpression;
import hw6.operation.abstractClasses.UnaryOperation;

public class BinaryNot extends UnaryOperation {
    public BinaryNot(TripleExpression value) {
        super(value);
    }

    protected int evaluate(int value) {
        return ~value;
    }
}
