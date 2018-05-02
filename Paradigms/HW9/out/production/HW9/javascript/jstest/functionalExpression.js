// var binaryFunction = function (h) {
//     return function (f, g) {
//         return function (x, y, z) {
//             return h(f(x, y, z), g(x, y, z))
//         }
//     }
// };
//
// var unaryFunction = function (h) {
//     return function (f) {
//         return function (x, y, z) {
//             return h(f(x, y, z))
//         }
//     }
// };

var cnst = function (arg) {
    return function () {
        return arg;
    }
};

var variable = function (arg) {
    var ind = ["x", "y", "z"].indexOf(arg);
    return function () {
        return arguments[ind];
        // switch (arg) {
        //     case "x":
        //         return arguments[0];
        //     case "y":
        //         return arguments[1];
        //     case "z":
        //         return arguments[2];
        // }
    }
};

var commonOperation = function (f) {
    return function () {
        var args = Array.prototype.slice.call(arguments);
        return function (x, y, z) {
            return f.apply(null, args.map(function (f) {
                return f(x, y, z);
            }));
        }
    }
};

var add = commonOperation(function (x, y) {
    return x + y;
});

var subtract = commonOperation(function (x, y) {
    return x - y;
});

var multiply = commonOperation(function (x, y) {
    return x * y;
});

var divide = commonOperation(function (x, y) {
    return x / y;
});

var negate = commonOperation(function (x) {
    return -x;
});

var cube = commonOperation(function (x) {
    return x * x * x;
});

var cuberoot = commonOperation(function (x) {
    return Math.pow(x, 1 / 3);
});

var min3 = commonOperation(function (a, b, c) {
    return Math.min(a, b, c);
});

var max5 = commonOperation(function (a, b, c, d, e) {
    return Math.max(a, b, c, d, e);
});

var pi = cnst(Math.PI);

var e = cnst(Math.E);

var x = variable("x");

var y = variable("y");

var z = variable("z");

var parse = function (expression) {
    var tokens = expression.split(' ');
    var stack = [];
    var tokensLen = tokens.length;
    for (var i = 0; i < tokensLen; i++) {
        switch (tokens[i]) {
            case "+":
                var sum = stack.pop();
                stack.push(add(stack.pop(), sum));
                break;
            case "-":
                var minus = stack.pop();
                stack.push(subtract(stack.pop(), minus));
                break;
            case "*":
                var mul = stack.pop();
                stack.push(multiply(stack.pop(), mul));
                break;
            case "/":
                var div = stack.pop();
                stack.push(divide(stack.pop(), div));
                break;
            case "cube":
                stack.push(cube(stack.pop()));
                break;
            case "cuberoot":
                stack.push(cuberoot(stack.pop()));
                break;
            case "min3":
                stack.push(min3(stack.pop(), stack.pop(), stack.pop()));
                break;
            case "max5":
                stack.push(max5(stack.pop(), stack.pop(), stack.pop(), stack.pop(), stack.pop()));
                break;
            case "negate":
                stack.push(negate(stack.pop()));
                break;
            case "":
                break;
            case "pi":
                stack.push(pi);
                break;
            case "e":
                stack.push(e);
                break;
            default:
                var token = parseInt(tokens[i]);
                if (isNaN(token)) {
                    stack.push(variable(tokens[i]));
                } else {
                    stack.push(cnst(token));
                }
        }
    }
    return stack.pop();
};


