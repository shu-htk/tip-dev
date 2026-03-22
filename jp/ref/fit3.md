# fit3
```
tip> fit3
Usage: fit3 x y z [plane] [(opt)]
Fit 3D data x,y,z with a plane.
Run 'plot3 x y z' before using this command.
Functions:
  plane : z = c0 + c1*x + c2*y
```

## fitting functions

|name | abbr. | function |
|:---:|:---:|:---:|
|plane| p | z = c0 + c1\*x + c2\*y |

## option

### option with single argument

- `lc:` line color of fitting plane
- `lt:` line style of fitting plane
- `rc:` flag to set relative coordinate for comment position
- `cf:` set tag of macro variable to store fitting coefficients
- `ez:` specify error data of z

### option with two arguments

> arguments is separated by comma with no spaces.

- cp: comment position of fitting information

for example, see [ex10](../../doc/ex/ex10.md)
