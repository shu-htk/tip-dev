# hplot2
```
tip> hplot2
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
- `lw:` line width, (default is 1)
- `rp:` replot flag
- `xt:` x-tick interval
- `yt:` y-tick interval
- `xn:` x-subtick num
- `yn:` y-subtick num
- `xm:` x margin factor, (default is 0.02)
- `ym:` y margin factor, (default is 0.1)
- `bo:` set box drawing order, (0=horizontal, 1=vertical)
- `bp:` set box positon, (from 1 to max number of divided frame)
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
|mesh2 | the same as mesh1 but colored proportionally to bins-entry |
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

example
```
tip> rm *
tip> set x=random(10000,gaus)
tip> set y=random(10000,gaus)
tip> hplot2 x y (nx:20 ny:20)

tip> ls *_mx,*_my,*_mz
x_mx : data(num) : size=42                ;# created data of x-axis-bin-center
y_my : data(num) : size=42                ;# created data of y-axis-bin-center
x_y_mz : data(mesh) : size_x=42 size_y=42 ;# created mesh data of bin-entry

tip> opt (xm:0 ym:0)
tip> mplot x_mx y_my x_y_mz (mt:mesh1)    ;# the same as hplot2 x y (mt:mesh1)
tip> mplot x_mx y_my x_y_mz (mt:mesh2)    ;# the same as hplot2 x y (mt:mesh2)
tip> mplot x_mx y_my x_y_mz (mt:cont1)    ;# the same as hplot2 x y (mt:cont1)
tip> mplot x_mx y_my x_y_mz (mt:cont2)    ;# the same as hplot2 x y (mt:cont2)
```
see also [mplot](mplot.md)

for more example, see
 [ex11](../ex/ex11.md),
 [ex12](../ex/ex12.md)
