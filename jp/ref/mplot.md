# mplot
```
tip> mplot
Usage: mplot x y z [(opt)]
Plot a 3D mesh graph.
  x : size N
  y : size M
  z : size N×M
Graph types (mt:):
  mesh1 : 3D mesh (single color)
  mesh2 : 3D mesh (gradation)
  cont1 : 2D contour (gray)
  cont2 : 2D contour (gradation)
```

## option

### option with single argument

- `mt:` mesh graph type (mesh1,mesh2,cont1,cont2),default is mesh1
- `lc:` line color of border
- `lt:` line style of border
- `lw:` line width, (default is 1)
- `rp:` replot flag
- `xt:` x-tick interval
- `yt:` y-tick interval
- `xn:` x-subtick num
- `yn:` y-subtick num
- `xm:` x margin factor, (default is 0.02)
- `ym:` y margin factor, (default is 0.1)
- `gd:` set flag to draw grid line, (0=not draw, 1=draw)
- `bo:` set box drawing order, (0=horizontal, 1=vertical)
- `bp:` set box position, (from 1 to max number of divided frame)
- `al:` altitude view angle , (default is 45 degree)
- `az:` azimuth view angle, (default is 45 degree)
- `zs:` z-axis scale (lin/log) 

> in `xm:` x margin means distance between maximum/minimum point of data
to left/right edge of x-axis

> in `ym:` y margin means distance between maximum/minimum point of data
to down/up edge of y-axis

### Mesh type specified by option `mt:`
|type | description|
|:---:|:---:|
|mesh1 | draw slope of 3D-mesh surface with single color |
|mesh2 | the same as mesh1 but colored proportionally z-value |
|cont1 | draw contours with gray-scale|
|cont2 | draw contours with color-scale|

### option with two arguments

> arguments is separated by comma with no spaces.

- `xr:` x-axis range (default 0,0 : range is automatically calculated)
- `yr:` x-axis range (default 0,0 : range is automatically calculated)

### option with quoted argument

- `tl:` title (see [title](title.md))
- `xl:` x-label (see [xlab](xlab.md))
- `yl:` y-label (see [ylab](ylab.md))
- `cc:` cut condition (see [cut](cut.md))

for example, see
[ex13a](../../doc/ex/ex13a.md),
[ex13b](../../doc/ex/ex13b.md),
[ex14](../../doc/ex/ex14.md)


