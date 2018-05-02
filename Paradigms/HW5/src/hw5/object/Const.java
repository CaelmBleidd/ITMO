package hw5.object;

import hw5.expression.MyInterface;

public class Const implements MyInterface {
    private final Number value;

    public Const(Number doubleValue) {
        this.value = doubleValue;
    }

    @Override
    public int evaluate(int x) {
        return value.intValue();
    }

    @Override
    public double evaluate(double x) {
        return value.doubleValue();
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return value.intValue();
    }
}
