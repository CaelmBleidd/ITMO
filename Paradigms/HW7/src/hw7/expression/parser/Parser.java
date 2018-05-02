package hw7.expression.parser;

import hw7.exceptions.FormatParserException;
import hw7.expression.*;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public interface Parser {
    TripleExpression parse(String expression) throws FormatParserException;
}
