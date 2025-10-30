# fit3
```
tip> fit3
usage: fit3 x y z [plane] [(opt)]
 do fitting to the data x,y,z by plane function.
 you should do 'plot3 x y z' before this command.
 available fitting functions:
   p[lane] : z = c0 + c1*x + c2*y
```

Fit the plane to data x, y and z after [plot3](plot3.md) command.
The fitting information is outputed to console and fitting plane is
drawn on the existing graph.
If you specify option `cp:X,Y`, the fitting information is drawn in
the graph at (X,Y).

**note)**  
> user defined fitting function is not available

## fitting functions

|name | abbr. | function |
|:---:|:---:|:---:|
|plane| p | z = c0 + c1\*x + c2\*y |

## option

### option with single argument

- lc: line color of fitting plane
- lt: line style of fitting plane
- rc: flag to set relative coordinate for comment position
- cf: set tag of macro variable to store fitting coefficients

### option with two arguments

> arguments is separated by comma with no spaces.

- cp: comment position of fitting information

for example, see [ex10](../ex/ex10.md)
