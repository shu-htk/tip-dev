# calc
```
tip> calc
usage: calc [expression]
```

this command show the result of calculation expression

where calculation expression is appear in

- [@](var.md) x = expr  
- [set](set.md) x = expr  

## operators

- **unary operator**

|function|operator|notation|
|:---:|:---:|:---:|
|positive| +|+ X|
|negative| -|- X|

```
tip> calc +3
[+3] -> [3]

tip> calc 2 * +3
[2 * +3] -> [6]

tip> calc -3
[-3] -> [-3]

tip> calc 2 * -3
[2 * -3] -> [-6]
```

- **binary operator**

|function|operator|notation|
|:---:|:---:|:---:|
|multiply |*|X * Y|
|divide   |/|X / Y|
|remainder|%|X % Y|
|add      |+|X + Y|
|subtract |-|X - Y|

```
tip> @ x=2
tip> @ y=3

tip> calc [x]+[y]
[2+3] -> [5]

tip> calc [x]*[y]
[2*3] -> [6]

tip> calc [x]/[y]
[2/3] -> [0.66666666667]

tip> calc [x]%[y]
[2%3] -> [2]

tip> calc [x]+[y]
[2+3] -> [5]

tip> calc [x]-[y]
[2-3] -> [-1]
```


## mathematical functions

`abs`,`sqrt`,`exp`,`log`,`log10`,`cos`,`acos`,`sin`,`asin`,`tan`,`atan`,`cosh`,`sinh`,`tanh`,`floor`,`pow`,`atan2`

see [ex02: Plot mathematical functions](../ex/ex02.md)
