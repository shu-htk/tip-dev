# box
```
tip> box
usage: box x0 x1 y0 y1 [(opt)]
```

draw 2-dimensional axis frame in the box shape.  
- x-axis range: from x0 to x1
- y-axis range: from y0 to y1

## option

### option with single argument

- `xt:` x-tick interval
- `yt:` y-tick interval
- `xn`: x-subtick num
- `yn`: y-subtick num
- `xs:` x-axis scale, (lin, log)
- `ys:` x-axis scale, (lin, log)
- `gd:` set flag to draw grid line, (0=not draw, 1=draw)
- `bo:` set box drawing order, (0=horizontal, 1=vertical)
- `bp:` set box position, (from 1 to max number of divided frame)
- `lw:` set box line width, (0=not draw, 1=draw)

### option with quoted argument

- `tl:` title (see [title](title.md))
- `xl:` x-label (see [xlab](xlab.md))
- `yl:` y-label (see [ylab](ylab.md))

see [ex16](../../doc/ex/ex16.md)


