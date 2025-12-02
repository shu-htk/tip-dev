# fit
```
tip> fit
usage: fit x y [lin|quad|exp|log|gaus|sin|circ] [(opt)]
 do fitting to the data x and y and draw the result.
 you should do 'plot x y' before this command.
 available fitting functions:
   l[in] : y = c0 + c1*x 
   q[uad]: y = c0 + c1*x + c2*x^2 
   e[xp] : y = c0*exp(c1*x) 
   log   : y = c0 + log(c1*x) 
   g[aus]: y = c0*exp(-(x-c1)^2/2*c2^2) 
   s[in] : y = c0 + c1*sin(2*PI*c3*x) + c2*cos(2*PI*c3*x) 
   c[irc]: (x-c0)^2 + (y-c1)^2 = c2^2 
```

Fit the curve to data x and y after [plot](plot.md) command.
The fitting information is outputted to console and fitting curve is
drawn on the existing graph.
If you specify option `cp:X,Y`, the fitting information is drawn in
the graph at (X,Y).

> user defined fitting function is not available

## fitting functions

|name | abbr. | function | option |
|:---:|:---:|:---:|:---:|
|lin  | l | y = c0 + c1*x || 
|quad | q | y = c0 + c1\*x + c2\*x^2 || 
|exp  | e | y = c0\*exp(c1\*x) ||
|log  |log| y = c0 + log(c1*x) ||
|gaus | g | y = c0\*exp(-(x-c1)^2/2\*c2^2) ||
|sin  | s | y = c0 + c1\*sin(2\*PI\*c3\*x) + c2\*cos(2\*PI\*c3\*x) |`fq:`| 
|circ | c | (x-c0)^2 + (y-c1)^2 = c2^2 ||

## option

### option with single argument

- `lc:` line color of fitting curve
- `lt:` line style of fitting curve
- `rc:` flag to set relative coordinate for comment position
- `cf:` set tag of macro variable to store fitting coefficients
- `fq:` set frequency of sinusoidal (sin) fitting

### option with two arguments

> arguments is separated by comma with no spaces.

- `cp:` comment position of fitting information

example
```
opt (lw:0 st:pls sc:red)

set x = range(50, 0.01, 0.5)

set y = 1.2 + 3.4*x
plot x y
fit x y lin (cf:a)    ;# store fitting coef to a0, a1

wait 0

set y = 1.2 + 3.4*x + 5.6*x*x
plot x y
fit x y quad (cf:b)   ;# store fitting coef to b0, b1, b2

wait 0

set y = 1.2*exp(3.4*x)
plot x y
fit x y exp (cf:c)    ;# store fitting coef to c0, c1

ls a?,b?,c?
```

result
```
@ Linear Fitting:
 y = c0 + c1*x
 c0=1.2
 c1=3.4
 chi2/ndf= 5.59e-29/48

@ Quadratic Fitting:
 y = c0 + c1*x + c2*x^2
 c0=1.2
 c1=3.4
 c2= 5.6
 chi2/ndf= 2.36e-27/47

@ Exponential Fitting:
 y = c0*exp(c1*x)
 c0=1.2
 c1=3.4
 chi2/ndf= 4.26e-29/48

a0 : number [1.2]
a1 : number [3.4]
b0 : number [1.2]
b1 : number [3.4]
b2 : number [5.6]
c0 : number [1.2]
c1 : number [3.4]
```

see [ex7a](../ex/ex07a.md), [ex7a](../ex/ex07b.md)
