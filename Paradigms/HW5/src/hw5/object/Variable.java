package hw5.object;

import hw5.expression.MyInterface;

public class Variable implements MyInterface {
    private String name;

    public Variable(String name) {
        this.name = name;
    }

    @Override
    public int evaluate(int x) {
        return name.equals("x") ? x : 0;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return name.equals("x") ? x : name.equals("y") ? y : name.equals("z") ? z : 0;
    }

    @Override
    public double evaluate(double doubleValue) {
        return name.equals("x") ? doubleValue : 0;
    }
}
