package hw5.operation;

import hw5.expression.MyInterface;

public class Add extends AbstractOperation {
    public Add(MyInterface firstOperand, MyInterface secondOperand) {
        super(firstOperand, secondOperand);
    }

    @Override
    public int evaluate(int firstOperand, int secondOperand) {
        return firstOperand + secondOperand;
    }

    @Override
    public double evaluate(double firstDoubleOperand, double secondDoubleOperand) {
        return firstDoubleOperand + secondDoubleOperand;
    }
}
