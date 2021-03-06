package hw6.operation.operations;

import hw6.expression.TripleExpression;
import hw6.operation.abstractClasses.*;

public class Add extends BinaryOperation {
    public Add(TripleExpression first, TripleExpression second) {
        super(first, second);
    }

    @Override
    protected int evaluate(int first, int second) {
        return first + second;
    }

}
