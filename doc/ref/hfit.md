# hfit
```
tip> hfit
usage: hfit v func [(opt)]
 you should do the 'hplot' before this command.
 'hplot' create a bin data v_hx, an entry data v_hy
 then 'fit v_hx v_hy func' is done.
 see the command 'fit' for the fitting functions.
```

It fits the curve to histogram of data v after [hplot](hplot.md) command.
The fitting information is outputted to console and fitting curve is
drawn on the existing graph.
If you specify option `cp:X,Y`, the fitting information is drawn in
the graph at (X,Y).

## fitting functions

see [fit](fit.md)

## option

### option with single argument

- `lc:` line color of fitting curve
- `lt:` line style of fitting curve
- `rc:` flag to set relative coordinate for comment position
- `cf:` set tag of macro variable to store fitting coefficients

### option with two arguments

> arguments is separated by comma with no spaces.

- `cp:` comment position of fitting information

for example, see [ex04](../ex/ex04.md), [ex20](../ex/ex20.md)

