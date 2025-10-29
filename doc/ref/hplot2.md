# hplot2
```
usage: hplot2 x y [(opt)]
 make and plot the 2D-histogram of data x and y
```

## option

### option with single argument

- `mt:` mesh graph type (mesh1,mesh2,cont1,cont2),default is mesh1
- `nx:` number of x-axis bins of 2D-histogram
- `ny:` number of y-axis bins of 2D-histogram
- `fc:` fill area color
- `ft:` fill area style
- `lc:` line color of border
- `lt:` line style of border
- `lw:` line width, (0=not draw, default is 1)
- `sc:` symbol color
- `st:` symbol style
- `ss:` symbol size, (default is 1)
- `rp:` replot flag
- `xt:` x-tick interval
- `yt:` y-tick interval
- `xn:` x-subtick num
- `yn:` y-subtick num
- `xs:` x-axis scale, (lin, log)
- `ys:` x-axis scale, (lin, log)
- `xm:` x margin factor, (default is 0.02)
- `ym:` y margin factor, (default is 0.1)
- `gd:` set flag to draw grid line, (0=not draw, 1=draw)
- `bo:` set box drawing order, (0=horizontal, 1=vertical)
- `bp:` set box positon, (from 1 to max number of divided frame)
- `mv:` moving average number
- `al:` altitude view angle , (default is 45 degree)
- `az:` azimuth view angle, (default is 45 degree)

> in `xm:` x margin means distance between maximum/minimum point of data
to left/right edge of x-axis

> in `ym:` y margin means distance between maximum/minimum point of data
to down/up edge of y-axis

### Mesh type specified by option `mt:`
|type | description|
|:---:|:---:|
|mesh1 | It is drawn by lego-shaped (rectangular parallelepiped)|
|mesh2 | same as mesh1 but colored proportionally to bins-entry |
|cont1 | It is drawn by contours with gray-scale|
|cont2 | It is drawn by contours with color-scale|

### option with two arguments

> arguments is separated by comma with no spaces.

- `xr:` x-axis range (default 0,0 : range is automatically calcurated)
- `yr:` x-axis range (default 0,0 : range is automatically calcurated)

### option with quotted argument by ""

- `tl:` title (see [title](title.md))
- `xl:` x-label (see [xlab](xlab.md))
- `yl:` y-label (see [ylab](ylab.md))
- `cc:` cut condition (see [cut](cut.md))

for example, see
 [ex11](../ex/ex11.md),
 [ex12](../ex/ex12.md)
