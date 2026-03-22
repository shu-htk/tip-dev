# hfit
```
tip> hfit
Usage: hfit v func [(opt)]
Fit the histogram created by 'hplot'.
Uses v_hx and v_hy, then runs: fit v_hx v_hy func.
```

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

for example, see [ex04](../../doc/ex/ex04.md), [ex20](../../doc/ex/ex20.md)

