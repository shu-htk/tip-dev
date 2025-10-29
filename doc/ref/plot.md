# plot
```
usage: plot [x] y [(opt)]
 plot the 2D-graph of data x and y.
 if data x is not specified the index data 'y_n' is created
 then 'plot y_n y' is done.
```

## option

> option tag and it's argument is separated by ':' with no spaces. 

### option with single argument

- `lc:` line color
- `lt:` line style
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

> in `xm:` x margin means distance between maximum/minimum point of data
to left/right edge of x-axis

> in `ym:` y margin means distance between maximum/minimum point of data
to down/up edge of y-axis

### option with two arguments

> arguments is separated by comma with no spaces.

- `xr:` x-axis range (default 0,0 : range is automatically calcurated)
- `yr:` x-axis range (default 0,0 : range is automatically calcurated)

### option with quotted argument by ""

- `tl:` title (see [title](title.md))
- `xl:` x-label (see [xlab](xlab.md))
- `yl:` y-label (see [ylab](ylab.md))
- `tf:` x-axis time format (see [tfmt](tfmt.md))
- `cc:` cut condition (see [cut](cut.md))

example
```
@ pi2=3.14159265*2
set t=range(50,0,[pi2])
set v=sin(t)

opt (gd:1 lw:0 st:pls sc:red)
div 1 2

title "Index vs Value of data v"
plot v   ;# index data 'v_n' is automatically generated

title "Value of data t vs v"
plot t v
```

