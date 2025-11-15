# exe
```
tip> exe
usage: exe [macro_file] [arg1,arg2,...] [(opt)]
 execute macro_file
 arguments are referenced as macro variables
 they are named like x1=val,x2=val2,...
 if it is specified only values like val1,val2,...
 they are named $1=val1,$2=val2,...
 number of argumnts is named $#
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

