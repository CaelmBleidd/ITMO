package hw5.operation;

import hw5.expression.MyInterface;

public abstract class AbstractOperation implements MyInterface {
    private final MyInterface firstOperand;
    private final MyInterface secondOperand;

    AbstractOperation(MyInterface firstOperand, MyInterface secondOperand) {
        assert firstOperand != null && secondOperand != null;
        this.firstOperand = firstOperand;
        this.secondOperand = secondOperand;
    }

    abstract int evaluate(int firstOperand, int secondOperand);

    abstract double evaluate(double firstDoubleOperand, double secondDoubleOperand);

    @Override
    public int evaluate(int intValue) {
        return evaluate(firstOperand.evaluate(intValue), secondOperand.evaluate(intValue));
    }

    @Override
    public double evaluate(double doubleValue) {
        return evaluate(firstOperand.evaluate(doubleValue), secondOperand.evaluate(doubleValue));
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return evaluate(firstOperand.evaluate(x, y, z), secondOperand.evaluate(x, y, z));
    }
}
