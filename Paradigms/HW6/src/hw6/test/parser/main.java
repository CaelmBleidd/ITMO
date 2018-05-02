package hw6.test.parser;

import hw6.expression.parser.Parser;
import hw6.parser.ExpressionParser;

public class main {
    public static void main(String[] args) {
        Parser parser = new ExpressionParser();
        int actual = parser.parse("(- - - x^1883669513)|(- x^1681810605)").evaluate(1, 2, 3);
        System.out.println(Integer.MAX_VALUE + " " + Integer.MIN_VALUE);
    }

}
