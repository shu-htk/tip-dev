# hplot
```
tip> hplot
Usage: hplot v [(opt)]
Create and plot a histogram of v.
Generates v_hx (bin centers) and v_hy (entries), then plots them.
Options:
  nb:N      number of bins
  xr:x0,x1  x‑range
If omitted, nb=100 and range is auto‑detected.
```

## option

### option with single argument

- `ht:` histogram type (bin1,bin2,slope) default is bin1
- `nb:` number of bins of 1D-histogram
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
- `bp:` set box position, (from 1 to max number of divided frame)
- `mv:` moving average number

> in `xm:` x margin means distance between maximum/minimum point of data
to left/right edge of x-axis

> in `ym:` y margin means distance between maximum/minimum point of data
to down/up edge of y-axis

### Histogram type specified by option `ht:`
|type | description|
|:---:|:---:|
|bin1 | histogram bins are not separated by vertical line|
|bin2 | histogram bins are separated by vertical line|
|slope| plot bins-center-values vs bins-entries by curve|

### option with two arguments

> arguments is separated by comma with no spaces.

- `xr:` x-axis range (default 0,0 : range is automatically calculated)
- `yr:` x-axis range (default 0,0 : range is automatically calculated)

### option with quoted argument

- `tl:` title (see [title](title.md))
- `xl:` x-label (see [xlab](xlab.md))
- `yl:` y-label (see [ylab](ylab.md))
- `cc:` cut condition (see [cut](cut.md))

example
```
tip> rm *
tip> set v=random(10000,gaus)
tip> hplot v (nb:100)        ;# make histogram of data v by nbin=100 and plot it

tip> ls *
v : data(num) : size=10000
v_hx : data(num) : size=100    ;# created data of bins-center
v_hy : data(num) : size=100    ;# created data of bins-entry

tip> plot v_hx v_hy (gt:bin1)  ;# the same as hplot v (ht:bin1)
tip> plot v_hx v_hy (gt:slope) ;# the same as hplot v (ht:slope) 
```

for more examples, see
 [ex04](../../doc/ex/ex04.md),
 [ex11](../../doc/ex/ex11.md),
 [ex12](../../doc/ex/ex12.md),
 [ex19](../../doc/ex/ex19.md),
 [ex20](../../doc/ex/ex20.md)
