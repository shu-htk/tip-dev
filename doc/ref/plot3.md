# plot3
```
tip> plot3
usage: plot3 x y z [(opt)]
 plot the 3d-graph of data x, y and z.
 those three data should be the same size.
```

## option

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
- `xm:` x margin factor, (default is 0.02)
- `ym:` y margin factor, (default is 0.1)
- `gd:` set flag to draw grid line, (0=not draw, 1=draw)
- `bo:` set box drawing order, (0=horizontal, 1=vertical)
- `bp:` set box positon, (from 1 to max number of divided frame)
- `al:` altitude view angle , (default is 45 degree)
- `az:` azimuth view angle, (default is 45 degree)

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
- `cc:` cut condition (see [cut](cut.md))

## set viewing angle (altitude / azimuth)

example
```
set t=range(100,0,30)
set x=cos(t)
set y=sin(t)

opt (lc:blue st:star sc:red)

opt (fl:0) ;# disable flushing to avoid display flickering

do al 10 50   ;# rotate altitude angle 10 - 50 [deg]
  plot3 x y t (al:[al])
  wait 0.01
end

wait 0

do az 10 50    ;# rotate azimuth angle 10 - 50 [deg]
  plot3 x y t (az:[az])
  wait 0.01
end
```

see also [ex10](../ex/ex10.md)

