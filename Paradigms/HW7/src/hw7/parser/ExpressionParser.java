package hw7.parser;

import hw7.exceptions.FormatParserException;
import hw7.operation.operations.*;
import hw7.object.*;
import hw7.expression.*;
import hw7.expression.parser.*;

public class ExpressionParser implements Parser {
    private String tmpLine;
    private int firstIndex;
    private int length;

    public TripleExpression parse(String s) throws FormatParserException {
        firstIndex = 0;
        tmpLine = s;
        length = tmpLine.length();
        TripleExpression result = AddSub();
        if (firstIndex != length) {
            String message;
            if (tmpLine.charAt(firstIndex) == ')') {
                message = "Can't find open parenthesis at index " + firstIndex + ": \n\t\t\t\t\t\t\t\t" + getOpenBracketException() + '\n';
                throw new FormatParserException(message);
            } else {
                message = getUnknownLexemeExceptionMessage();
                throw new FormatParserException(message);
            }
        }
        return result;
    }


    private void skipSpace() {
        while (firstIndex < length && Character.isWhitespace(tmpLine.charAt(firstIndex))) {
            firstIndex++;
        }
    }


    private TripleExpression AddSub() throws FormatParserException {
        TripleExpression current;
        TripleExpression tmpOperand = mulDiv();
        while (firstIndex < length && tmpLine.charAt(firstIndex) != ')') {
            if (!(tmpLine.charAt(firstIndex) == '+' || tmpLine.charAt(firstIndex) == '-'))
                break;
            char sign = tmpLine.charAt(firstIndex);
            firstIndex++;
            current = mulDiv();
            if (sign == '+') {
                tmpOperand = new CheckedAdd(tmpOperand, current);
            } else {
                tmpOperand = new CheckedSubtract(tmpOperand, current);
            }
        }
        return tmpOperand;
    }


    private TripleExpression mulDiv() throws FormatParserException {
        TripleExpression current = operand();
        while (true) {
            skipSpace();
            if (firstIndex >= length) {
                return current;
            }
            char sign = tmpLine.charAt(firstIndex);
            if ((sign != '*' && sign != '/'))
                return current;
            firstIndex++;
            TripleExpression right = operand();
            if (sign == '*') {
                current = new CheckedMultiply(current, right);
            } else {
                current = new CheckedDivide(current, right);
            }
        }
    }

    private TripleExpression operand() throws FormatParserException {
        skipSpace();
        String message;
        if (length == firstIndex) {
            String prevExpression = getPrevArg(false);
            throw new FormatParserException("Expected argument, found end of expression at index " + (firstIndex - 1) + ":"
                    + "\n\t\t\t\t\t\t\t\t" + prevExpression + "<missing argument>" + '\n');
        }
        char c = tmpLine.charAt(firstIndex);
        switch (c) {
            case 'l':
                if (checkLog10()) {
                    return powLog10(false);
                } else {
                    if (firstIndex + 5 >= length) {
                        throw new FormatParserException("Expected argument, found nothing at index " + (firstIndex + 5) + ":\n\t\t\t\t\t\t\t\t" + getWord() + '\n');
                    }
                    throw new FormatParserException("Expected log10, found unknown lexeme at index " + firstIndex
                            + ":\n\t\t\t\t\t\t\t\t" + getWord() + '\n');
                }
            case 'p':
                if (checkPow10()) {
                    return powLog10(true);
                } else {
                    throw new FormatParserException("Expected pow10, found " + c + "* at index " + firstIndex
                            + ":\n\t\t\t\t\t\t\t\t" + getWord() + '\n');
                }
            case ')':
                message = getCloseOpenBracketException();
                switch (message) {
                    case "log10(":
                        throw new FormatParserException("Syntax parser exception : empty argument of logarithm at index " + firstIndex
                                + ":\n\t\t\t\t\t\t\t\t" + message + "\n");
                    case "pow10(":
                        throw new FormatParserException("Syntax parser exception : empty argument of pow at index " + firstIndex
                                + ":\n\t\t\t\t\t\t\t\t" + message + "\n");
                    default:
                        throw new FormatParserException("Syntax parser exception : unexpected close bracket at index " + firstIndex
                                + ":\n\t\t\t\t\t\t\t\t" + message + '\n');
                }

            case '(':
                return bracket();
            case 'x':
            case 'y':
            case 'z':
                firstIndex++;
                return new Variable(String.valueOf(c));
            case '-':
                firstIndex++;
                skipSpace();
                if (firstIndex < length && Character.isDigit(tmpLine.charAt(firstIndex))) {
                    StringBuilder sb = new StringBuilder("-");
                    while (firstIndex < length && Character.isDigit(tmpLine.charAt(firstIndex))) {
                        sb.append(tmpLine.charAt(firstIndex++));
                    }
                    int tmp;
                    try {
                        tmp = Integer.parseInt(sb.toString());
                    } catch (NumberFormatException e) {
                        throw new FormatParserException("Illegal number at index " + firstIndex +
                                ":\n\t\t\t\t\t\t\t\t" + sb.toString() + '\n');
                    }
                    return new Const(tmp);
                } else {
                    return new CheckedNegate(operand());
                }

            default:
                skipSpace();
                StringBuilder strNumber = new StringBuilder();
                while (firstIndex < length && (Character.isDigit(tmpLine.charAt(firstIndex)))) {
                    strNumber.append(tmpLine.charAt(firstIndex++));
                }
                if (strNumber.toString().equals("")) {
                    char op = tmpLine.charAt(firstIndex);
                    if (op != '+' && op != '-' && op != '*' && op != '/') {
                        message = getUnknownLexemeExceptionMessage();
                        throw new FormatParserException(message);
                    }
                    message = getArgumentException();
                    throw new FormatParserException(message);
                }
                int val;
                try {
                    val = Integer.parseInt(strNumber.toString());
                } catch (NumberFormatException e) {
                    if (firstIndex < length && firstIndex - strNumber.length() - 1 >= 0 && tmpLine.charAt(firstIndex - strNumber.length() - 1) == '-') {
                        message = '-' + strNumber.toString();
                    } else {
                        message = strNumber.toString();
                    }
                    throw new FormatParserException("Illegal number at index " + firstIndex +
                            ":\n\t\t\t\t\t\t\t\t" + message + '\n');
                }
                return new Const(val);
        }
    }

    private TripleExpression bracket() throws FormatParserException {
        firstIndex++;
        TripleExpression tmpOperand = AddSub();
        if (length == firstIndex) {
            throw new FormatParserException("Can't find close parenthesis at index " + firstIndex
                    + ":\n\t\t\t\t\t\t\t\t" + getCloseOpenBracketException() + '\n');
        }
        if (firstIndex < length && tmpLine.charAt(firstIndex) == ')') {
            firstIndex++;
            return tmpOperand;
        } else {
            throw new FormatParserException("Unexpected symbol in constant at index " + firstIndex +
                    ":\n\t\t\t\t\t\t\t\t" + getPrevArg(false) + tmpLine.charAt(firstIndex) + getNextArg() + '\n');
        }
    }

    private TripleExpression powLog10(boolean type) throws FormatParserException {
        TripleExpression tmpOperand;
        firstIndex += 5;
        tmpOperand = operand();
        if (type) {
            return new CheckedPow10(tmpOperand);
        } else {
            return new CheckedLog10(tmpOperand);
        }
    }

    private boolean checkLog10() {
        skipSpace();
        return firstIndex + 5 < length && getFunc().equals("log10");
    }

    private boolean checkPow10() {
        skipSpace();
        return firstIndex + 5 < length && getFunc().equals("pow10");
    }

    private String getFunc() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 5; i++) {
            sb.append(tmpLine.charAt(firstIndex + i));
        }
        return sb.toString();
    }


    private String getArgumentException() {
        String message;
        String nextArg = getNextArg();
        char curOp = tmpLine.charAt(firstIndex);
        String prevExpression = getPrevArg(true);
        if (prevExpression.equals("")) {
            message = "Can't find first argument at index " + firstIndex +
                    ":\n\t\t\t\t\t\t\t\t <missing argument>" + curOp + nextArg + '\n';
        } else {
            message = "Can't find middle argument at index " + firstIndex +
                    ":\n\t\t\t\t\t\t\t\t" + prevExpression + "<missing argument> " + curOp + nextArg + '\n';
        }
        return message;
    }

    private String getUnknownLexemeExceptionMessage() {
        String message;
        String prevExpression = getPrevArg(true);
        String nextExpression = getNextArg();
        char op = tmpLine.charAt(firstIndex);
        if (prevExpression.equals("")) {
            message = "Unexpected start character " + op + " at index " + firstIndex
                    + ":\n\t\t\t\t\t\t\t\t" + op + nextExpression + '\n';
        } else if (nextExpression.equals("")) {
            message = "Unexpected end character " + op + " at index " + firstIndex
                    + ":\n\t\t\t\t\t\t\t\t" + prevExpression + op + '\n';
        } else {
            message = "Unexpected middle character " + tmpLine.charAt(firstIndex) + " at index " + firstIndex
                    + ":\n\t\t\t\t\t\t\t\t" + getPrevArg(true) + tmpLine.charAt(firstIndex) + getNextArg() + '\n';
        }
        return message;
    }


    private String getNextArg() {
        int start = firstIndex + 1;
        if (start == length) return "";
        char c = tmpLine.charAt(start);
        int balance = 0;
        StringBuilder sb = new StringBuilder();
        while (start < length && !Character.isDigit(c) && c != 'x' && c != 'y' && c != 'z') {
            if (c == '(') {
                balance++;
            } else if (c == ')') {
                balance--;
            }
            sb.append(c);
            if (++start == length) return sb.toString();
            c = tmpLine.charAt(start);
        }
        if (balance > 0) {
            while (start != length && balance != 0) {
                c = tmpLine.charAt(start++);
                if (c == '(') {
                    balance++;
                } else if (c == ')') {
                    balance--;
                }
                sb.append(c);
            }
            return sb.toString();
        } else {
            if (c == 'x' || c == 'y' || c == 'z') {
                sb.append(c);
                return sb.toString();
            } else {
                while (start != length && Character.isDigit(c)) {
                    sb.append(c);
                    if (++start == length) break;
                    c = tmpLine.charAt(start);
                }
                return sb.toString();
            }
        }
    }


    private String getPrevArg(boolean withOp) {
        int start = Math.max(0, firstIndex - 1);
        if (start == 0)
            return "";

        int end = firstIndex;
        while (start > 0 && Character.isWhitespace(tmpLine.charAt(start))) {
            start--;
        }
        if (start == 0)
            return String.valueOf(tmpLine.charAt(0));

        start--;
        char c = tmpLine.charAt(start);
        while (start > 0 && c != ')' && c != '(' && c != '*' && c != '/' && c != '+' && c != '-') {
            c = tmpLine.charAt(--start);
        }

        int balance = 0;
        if (c == ')') {
            balance++;
            start--;
            while (start > 0 && balance != 0) {
                c = tmpLine.charAt(start--);
                if (c == ')') {
                    balance++;
                } else if (c == '(') {
                    balance--;
                }
            }
            if (start == 0)
                return substring(firstIndex, end);

            c = tmpLine.charAt(start);
            while (start > 0 && c != '*' && c != '/' && c != '+' && c != '-') {
                c = tmpLine.charAt(--start);
            }
        }
        return substring(withOp ? start : start + 1, end);

    }

    private String getCloseOpenBracketException() {
        int start = firstIndex - 1;
        while (start > 0 && tmpLine.charAt(start) != ')') {
            start--;
        }
        return substring(start, firstIndex) + " <missing argument> ";
    }

    private String getOpenBracketException() {
        int start = firstIndex - 1;
        while (start > 0 && tmpLine.charAt(start) != '(') {
            start--;
        }
        return "<missing argument> " + substring(start, firstIndex + 1);
    }

    private String substring(int start, int end) {
        StringBuilder sb = new StringBuilder();
        for (int i = start; i < end; i++) {
            sb.append(tmpLine.charAt(i));
        }
        return sb.toString();
    }

    private String getWord() {
        int start = firstIndex;
        StringBuilder sb = new StringBuilder();
        while (start < length &&
                (Character.isAlphabetic(tmpLine.charAt(start))
                        || Character.isDigit(tmpLine.charAt(start))
                        || tmpLine.charAt(start) == ')'
                        || tmpLine.charAt(start) == '(')) {
            sb.append(tmpLine.charAt(start++));
        }
        return sb.toString();
    }
}