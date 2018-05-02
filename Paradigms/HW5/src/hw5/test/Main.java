package hw5.test;

import hw5.object.Const;
import hw5.object.Variable;
import hw5.operation.Multiply;
import hw5.operation.Subtract;

public class Main {
    public static void main(String[] args) {
        int a = new Subtract(new Multiply(new Const(2), new Variable("x")), new Const(3)).evaluate(5);
        System.out.println(a);
    }
}
