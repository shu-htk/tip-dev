# box3
```
tip> box3
usage: box3 x0 x1 y0 y1 z0 z1 [(opt)]
```

draw 3-dimensional axis frame.

- x-axis range: from x0 to x1
- y-axis range: from y0 to y1
- z-axis range: from z0 to z1

## option

### option with single argument

- `xt:` x-tick interval
- `yt:` y-tick interval
- `xn`: x-subtick num
- `yn`: y-subtick num
- `bo:` set box drawing order, (0=horizontal, 1=vertical)
- `bp:` set box position, (from 1 to max number of divided frame)
- `al:` altitude view angle , (default is 45 degree)
- `az:` azimuth view angle, (default is 45 degree)

### option with quoted argument

- `tl:` title (see [title](title.md))
- `xl:` x-label (see [xlab](xlab.md))
- `yl:` y-label (see [ylab](ylab.md))
- `zl:` z-label (see [zlab](zlab.md))

