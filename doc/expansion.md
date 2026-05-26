## Macro Variable Expansion

> Feature added in v1.2

When expanding macro variables into a string by enclosing them in square brackets `[]`, the following specifications are now supported.

## (1) Format Specification

You can specify the format by prefixing the variable name with a colon, as shown below:

```
[%fmt:var]

```

Prior to v1.2, this had to be specified using the `fmt` command, for example:

```
tip> @ x=exp(10)

tip> fmt %10.2e
tip> prn [x]
  2.20e+04

```

However, from v1.2 onwards, you can combine multiple formats in a single line like this:

```
tip> fmt reset
tip> prn default format: [x], specified format: [%10.2e:x]
default format: 22026.465795, specified format:   2.20e+04

```

## (2) Evaluating and Expanding Mathematical Expressions

```
[expr(var)]

```

You can now write a mathematical expression containing macro variables inside the square brackets `[]` and expand the calculated result into a string.

Example:

```
tip> @ pi=acos(-1)

tip> prn [2*pi]
6.2831853072

```

As a side note, `2*[pi]` is evaluated after `pi` is expanded into a string, whereas `[2*pi]` performs the calculation first and then expands the result into a string.

Example:

```
tip> calc 2*[pi]
[2*3.1415926536] -> [6.2831853072]

tip> calc [2*pi]
[6.2831853072] -> [6.2831853072]

```

Expression evaluation can be used simultaneously with format specification.

Example:

```
tip> prn [%.2f:2*pi]
6.28

```

You can also include spaces in the format separator and within the mathematical expression.

Example:

```
tip> prn [%.2f : 2 * pi]
6.28

```
