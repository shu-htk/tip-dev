# exe
```
usage: exe [macro_file] [(opt)]
 execute macro_file
```

## option

- `dm:` set flag of debug-mode, 0:not set, 1: set

## Execute macro file with debug-mode

Usually variables defined in the macro file can not be referenced from
the interactive console.  
Executing with debug-mode, variables in the macro file can be
referenced from the interactive console.

example
```
tip> rm *
tip> exe doc/macro/tut01.tip   ;# execute macro file without debug-mode
@ Quadratic Fitting:
 y = c0 + c1*x + c2*x^2
 c0=-1.36424e-12
 c1=2.27374e-13
 c2= 2
 chi2/ndf= 8.15e-25/7

tip> ls *   ;# variables defined in the macro file can not be referenced

tip> exe doc/macro/tut01.tip (dm:1)  ;# execute macro file with debug-mode
@ Quadratic Fitting:
 y = c0 + c1*x + c2*x^2
 c0=-1.36424e-12
 c1=2.27374e-13
 c2= 2
 chi2/ndf= 8.15e-25/7

tip> ls *    ;# variables defined in the macro file can be referenced
x : data(num) : size=10
y : data(num) : size=10
```

