package hw7.test;

import hw7.expression.parser.Parser;
import hw7.parser.ExpressionParser;

import static java.lang.Thread.sleep;

public class MyTest {
    public static void main(String[] args) {
        testParser();
    }
    public static void testParser() {
        testTokens();
        testWithoutBrackets();
        testUnary();
        testBrackets();
        testBitwise();
        testErrors();
        System.out.println("Good!");
    }

    private static void test(String expression, int expected, int ... variables) {
        try {
            sleep(150);
        } catch (InterruptedException e) {
            System.out.println("Uuuuuuuuuh");
        }
        System.out.println("Testing " + expression);
        Parser parser = new ExpressionParser();
        try {
            int actual = parser.parse(expression).evaluate(variables[0], variables[1], variables[2]);
            assert expected == actual : String.format("Expected: %d, actual: %d", expected, actual);
        } catch (ArithmeticException e) {
            //System.err.println(e.getMessage());
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }

    }

    private static void test(String expression, int expected) {
        test(expression, expected, 1, 2, 3);
    }

    private static void testTokens() {
        printTitle("Const and variables");
        test("10", 10);
        test("x", 1);
    }

    private static void testBitwise() {
        printTitle("Bitwise");
        test("1 & 2", 0);
        test("6 & 1 + 2", 2);
        test("6 ^ 1 + 2", 5);
        test("6 | 1 + 2", 7);
        test("1 | 2 | 3 ^ 4 & 5 * 6 - 7", 7);
        test("6 ^ 5 & 4 | 3 + 2 * 10", 23);
        test("-(((((6 ^ 5) & 4) | 3) + 2) * 10)", -50);
        test("x ^ - y + (y / z / y) + (y * -2 / x) | y ^ z - - x & -3 | z - (4 / y)", -1);
        test("(y * -2 / x) | y ^ z - - x & -3", -2);
        test("y ^ z - - x & -3", 6);

        test("8 - y & - 9 * x & - 10 / 11 - -12 / 13 | x", 1);

        test("5 * (-6 & -7 * (8 - y & - 9 * x & - 10 / 11 - -12 / 13 | x))", -40);

        test("x ^ - y + y / z / y + y * -2 / x " +
                "| (y) ^ z - (- x) & -3 " +
                "| z - 4 / y + (5) * (-6 " +
                "& -7 * (8 - y & - 9 * x " +
                "& - 10 / 11 - -12 / 13 | x))", -1);

        test("(- - z | x ^ z ^ z & 4 - 5)", 3);
        test("(- - z | x ^ z ^ z & 4 - 5) | y * - - - -6", 15);
        test("2 * (3) / (x) + (- - z | x ^ z ^ z & 4 - 5) | y * - - - -6", 13);
        test("countcountcountcountcountcountcountcountcountcount -2147483648", 1);
    }

    private static void testBrackets() {
        printTitle("Brackets");
        test("(1)", 1);
        test("-(x)", -1);
        test("(1 + 2)", 3);
        test("1 + (2 * (3 + 4) / 5)", 3);
        test("2 * (3 - 4) * 5", -10);
        test("2 * -(3 - 4) * 5", 10);
        test("3 * ((2 + 1) / 3) * 1", 3);
        test("1 + 2 + 3 * ((2 + 1) / 3) * (1 + 2) + 4 + 1", 17);
        test("(1 + 2 + 3 * ((2 + 1) / 3) * (1 + 2) + 4 + 1)", 17);
        test("-(1 + 2 + 3 * ((2 + 1) / 3) * (1 + 2) + 4 + 1)", -17);
        test("-((((2))))", -2);
        test("-(- -5 + 16*x*y)", -37);
        test("-(-(-\t\t-5 + 16   *x*y) + 1 * z) -(((-11)))", 45);
        test("- - (z) / x * - (- - x * ((-5 / y - -7)))", -15);
        test("((-1 / y - -2))", 2);
        test("y / z - 1445226260 // (1618638729) / - - - z", -5, -1878751135, 1513253546, -290208276);
    }

    private static void testUnary() {
        printTitle("Unary operations");
        test("-10", -10);
        test("--10", 10);
        test("2 / -1", -2);
        test("2 /--1", 2);
        test("-2 / -1", 2);
        test("2 / -x", -2);
    }

    private static void testWithoutBrackets() {
        printTitle("Expressions without brackets");
        test("2 * 3 - 4 * 5 - 6", -20);
        test("2 - 3 * 4 * 5 + 3", -55);
        test("2 * 3 - 4 * 5", -14);
        test("2 * 3 * 4 - 5", 19);
        test("2 + 2 + 2", 6);
        test("2 + 2 + 2 * 5", 14);
        test("2 * 2 * 2 * 2", 16);
    }

    private static void testErrors() {
        testOverflow();
        testParsingErrors();
    }

    private static void testOverflow() {
        printTitle("Overflow");
        test("2/0", 0);
    }

    private static void testParsingErrors() {
        printTitle("Parsing errors");
        test("x*y%+(z-1   )/10", 2);
        test("(1+)", 0);
        test("+", 0);
        test("(1 + 2", 0);
        test("1 + 2)", 0);
        test("1 + 2A", 0);
        test("2 *", 0);
    }

    private static void printTitle(String message) {
        System.out.println("\n" + message + "\n====================");
    }
}
