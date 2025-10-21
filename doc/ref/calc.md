# calc
```
usage: calc [expression]
```

this command show the result of "calculation expression"

where "calculation expression" is appear in

- [@](var.md) x = expr  
- [set](set.md) x = expr  

## operators

- **unary operator**

|operator|function|
|-|-|
|+|positive|
|\-|negative|

```
tip> calc +3
expression: [+3]
result: 3
tip> calc 2 * +3
expression: [2 * +3]
result: 6

tip> calc -3
expression: [-3]
result: -3
tip> calc 2 * -3
expression: [2 * -3]
result: -6
```

- **binary operator**

|operator|function|
|-|-|
|*|multiply|
|/|divide|
|%|remainder|
|+|add|
|\-|subtract|


## mathematical functions

`abs`,`sqrt`,`exp`,`log`,`log10`,`cos`,`acos`,`sin`,`asin`,`tan`,`atan`,`cosh`,`sinh`,`tanh`,`floor`,`pow`,`atan2`

see [ex02: Plot mathematical functions](../ex/ex02.md)
