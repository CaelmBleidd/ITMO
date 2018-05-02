package hw6.parser;

import hw6.operation.operations.*;
import hw6.object.*;
import hw6.expression.*;
import hw6.expression.parser.*;

public class ExpressionParser implements Parser {
    private String tmp;
    private int firstIndex;
    private boolean intMin = false;
    private int length;

    @Override
    public TripleExpression parse(String s) {
        firstIndex = 0;
        tmp = s;
        length = tmp.length();
        return binaryOr();
    }

    private void skipSpace() {
        while (firstIndex < length && Character.isWhitespace(tmp.charAt(firstIndex))) {
            firstIndex++;
        }
    }

    private TripleExpression binaryOr() {
        TripleExpression current;
        TripleExpression acc = binaryXor();
        while (firstIndex < length && tmp.charAt(firstIndex) != ')') {
            if (!(tmp.charAt(firstIndex) == '|')) break;
            firstIndex++;
            current = binaryXor();
            acc = new BinaryOr(acc, current);
        }
        return acc;
    }

    private TripleExpression binaryXor() {
        TripleExpression current;
        TripleExpression acc = binaryAnd();
        while (firstIndex < length) {
            if (!(tmp.charAt(firstIndex) == '^')) break;
            firstIndex++;
            current = binaryAnd();
            acc = new BinaryXor(acc, current);
        }
        return acc;
    }

    private TripleExpression binaryAnd() {
        TripleExpression current;
        TripleExpression acc = addSubtract();
        while (firstIndex < length) {
            if (!(tmp.charAt(firstIndex) == '&')) break;
            firstIndex++;
            current = addSubtract();
            acc = new BinaryAnd(acc, current);
        }
        return acc;
    }

    private TripleExpression addSubtract() {
        TripleExpression current;
        TripleExpression acc = mulDiv();
        while (firstIndex < length) {
            if (!(tmp.charAt(firstIndex) == '+' || tmp.charAt(firstIndex) == '-')) break;
            char sign = tmp.charAt(firstIndex);
            firstIndex++;
            current = mulDiv();
            if (sign == '+') {
                acc = new Add(acc, current);
            } else {
                acc = new Subtract(acc, current);
            }
        }
        return acc;
    }

    private TripleExpression mulDiv() {
        TripleExpression current = operand();
        while (true) {
            skipSpace();
            if (firstIndex >= length) {
                return current;
            }
            char sign = tmp.charAt(firstIndex);
            if ((sign != '*' && sign != '/')) return current;
            firstIndex++;
            TripleExpression right = operand();

            if (sign == '*') {
                current = new Multiply(current, right);
            } else {
                current = new Divide(current, right);
            }
        }
    }

    private TripleExpression operand() {
        skipSpace();
        boolean count = false;
        char c = tmp.charAt(firstIndex);
        switch (c) {
            case '(':
                return bracket();
            case 'x':
            case 'y':
            case 'z':
                firstIndex++;
                return new Variable(String.valueOf(c));
            case 'c':
                count = true;
            case '-':
            case '~':
                firstIndex += count ? 5 : 1;
                skipSpace();
                //TripleExpression current = operand();
//                if (c == '-') {
//                    if (intMin) {
//                        intMin = false;
//                        return current;
//                    } else
//                        return new UnaryMinus(current);

                if (c == '-') {
                    skipSpace();
                    if (Character.isDigit(tmp.charAt(firstIndex))) {
                        StringBuilder sb = new StringBuilder("-");
                        while (firstIndex < length && Character.isDigit(tmp.charAt(firstIndex))) {
                            sb.append(tmp.charAt(firstIndex++));
                        }
                        return new Const(Integer.parseInt(sb.toString()));
                    } else {
                        return new UnaryMinus(operand());
                    }
                } else if (c == '~') {
                    return new BinaryNot(operand());
                } else {
                    return new Count(operand());
                }
            default:
                skipSpace();
                StringBuilder strNumber = new StringBuilder();
                while (firstIndex < tmp.length() && (Character.isDigit(tmp.charAt(firstIndex)))) {
                    strNumber.append(tmp.charAt(firstIndex++));
                }
                //       if (strNumber.toString().equals("2147483648")) {
                //           intMin = true;
                //           return new Const(-2147483648);
                //       }
                int val = Integer.parseInt(strNumber.toString());
                return new Const(val);
        }
    }

    private TripleExpression bracket() {
        firstIndex++;
        TripleExpression acc = binaryOr();
        firstIndex++;
        return acc;
    }
}