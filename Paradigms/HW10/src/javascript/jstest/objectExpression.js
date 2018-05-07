function operation(evalFunction, diffFunction, nameOfOperate, numberOfArguments) {
    function Constructor() {
        this.args = toArray(arguments)
    }

    Constructor.prototype.toString = function () {
        return this.args.map(getString).join(" ") + " " + nameOfOperate
    };
    Constructor.prototype.evaluate = function (x, y, z) {
        return evalFunction.apply(null, this.args.map(getValue(arguments)))
    };
    Constructor.prototype.diff = function (arg) {
        return diffFunction(this, arg)
    };
    Constructor.prototype.numberOfArguments = numberOfArguments;
    operators[nameOfOperate] = Constructor;
    return Constructor;
}

function toArray(args) {
    var r = [];
    r.push.apply(r, args);
    return r;
}

function getValue(args) {
    return function (expression) {
        return expression.evaluate.apply(expression, args);
    }
}

function getString(expression) {
    return expression.toString();
}

function Const(arg) {
    this.cnst = arg
}

function Variable(arg) {
    this.v = arg
}

Const.prototype.toString = function () {
    return this.cnst.toString()
};

Const.prototype.evaluate = function () {
    return this.cnst
};

Const.prototype.diff = function () {
    return new Const(0)
};

var vars = ["x", "y", "z"];

Variable.prototype.toString = function () {
    return this.v
};

Variable.prototype.evaluate = function () {
    return arguments[vars.indexOf(this.v)]
};

Variable.prototype.diff = function (arg) {
    return new Const(arg === this.v ? 1 : 0)
};

var operators = [];

var Add = operation(function (x, y) {
    return x + y
}, function (operands, arg) {
    return new Add(operands.args[0].diff(arg), operands.args[1].diff(arg))
}, "+", 2);

var Subtract = operation(function (x, y) {
    return x - y
}, function (operands, arg) {
    return new Subtract(operands.args[0].diff(arg), operands.args[1].diff(arg))
}, "-", 2);

var Multiply = operation(function (x, y) {
    return x * y
}, function (operands, arg) {
    return new Add(new Multiply(operands.args[0].diff(arg), operands.args[1]), new Multiply(operands.args[0], operands.args[1].diff(arg)))
}, "*", 2);

var Divide = operation(function (x, y) {
    return x / y
}, function (operands, arg) {
    return new Divide(new Subtract(new Multiply(operands.args[0].diff(arg), operands.args[1]), new Multiply(operands.args[0], operands.args[1].diff(arg))),
        new Multiply(operands.args[1], operands.args[1]))
}, "/", 2);

var Negate = operation(function (x) {
    return -x
}, function (operand, arg) {
    return new Negate(operand.args[0].diff(arg))
}, "negate", 1);

var Square = operation(function (x) {
    return Math.pow(x, 2)
}, function (operand, arg) {
    return new Multiply(new Multiply(new Const(2), operand.args[0]), operand.args[0].diff(arg))
}, "square", 1);

var Sqrt = operation(function (x) {
    return Math.sqrt(Math.abs(x))
}, function (operand, arg) {
    return new Divide(new Multiply(operand.args[0], operand.args[0].diff(arg)),
        new Multiply(new Const(2), new Sqrt(new Multiply(new Square(operand.args[0]), operand.args[0]))))
}, "sqrt", 1);

var Pow = operation(function (x, y) {
    return Math.pow(x, y)
}, function (operand, arg) {
    return new Multiply(new Multiply(new Const(), operand.args[0]), operand.args[0].diff(arg))
}, "pow", 2);

var Log = operation(function (x, y) {
    return Math.abs(Math.log(x)) / Math.abs(Math.log(y))
}, function (operand, arg) {
    return new Divide(new Multiply(operand.args[0], operand.args[0].diff(arg)),
        new Multiply(new Const(), new Sqrt(new Multiply(new Square(operand.args[0]), operand.args[0]))))
}, "log", 2);

var parse = function (expression) {
    var tokens = expression.split(' ');
    var stack = [];
    var tokensLen = tokens.length;
    for (var i = 0; i < tokensLen; i++) {
        if (operators[tokens[i]] !== undefined) {
            var f = operators[tokens[i]];
            var n = f.prototype.numberOfArguments;
            var expr = Object.create(f.prototype);
            var args = stack.splice(stack.length - n, n);
            f.apply(expr, args);
            stack.push(expr);
        } else if (tokens[i] === "") {
        } else if (isNumber(tokens[i])) {
            stack.push(new Const(parseInt(tokens[i])));
        } else {
            stack.push(new Variable(tokens[i]));
        }
    }
    return stack[0];

    function isNumber(n) {
        return !isNaN(parseInt(n));
    }
};
