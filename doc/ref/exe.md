# exe
```
usage: exe [macro_file] [(opt)]
 execute macro_file
```

## option

- `dm:` set flag of debug mode, 0:not set, 1: set

## Execute the tip macro with debug mode

Usually variables defind in the macro file are removed when it is finished, so 
they can't be used in the interactive console.
If the macro file is executed with debug mode, variables in the macro file are
remained and able to handle in the interactive console.

example
```
$ cat doc/macro/tut01.tip
title "Plotting the data and fitting the curve"
set x = {1,2,3,4,5,6,7,8,9,10}
set y = 2*x*x
plot x y (lw:0 st:star sc:red gd:1)
fit x y quad (cp:1,200 lc:blue)
```
```
tip> rm *   ;# remove all variables
tip> exe doc/macro/tut01.tip   ;# execute the macro without debug mode
@ Quadratic Fitting:
 y = c0 + c1*x + c2*x^2
 c0=-1.36424e-12
 c1=2.27374e-13
 c2= 2
 chi2/ndf= 8.15e-25/7

tip> ls *   ;# variables defined in the macro are removed

tip> exe doc/macro/tut01.tip (dm:1)  ;# execute the macro without debug mode
@ Quadratic Fitting:
 y = c0 + c1*x + c2*x^2
 c0=-1.36424e-12
 c1=2.27374e-13
 c2= 2
 chi2/ndf= 8.15e-25/7

tip> ls *    ;# variables defined in the macro are remaind
x : data(num) : size=10
y : data(num) : size=10
```

