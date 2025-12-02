# fplot
```
tip> fplot
usage: fplot [t] v [(opt)]
 do FFT with the time data t and the amplitude v.
 it is created the frequency data v_fx and the power spectrum v_fy.
 then 'plot v_fx v_fy' is done.
 if data t is not specified you should set the option 'dt:'
options:
 dt:x   the time tick of FFT. (default is 1.0)
 fw:s   FFT window function. (default is 'rc'(Rectangle))
 name of window functions are
  rc  : Rectangle (default)
  hn  : Hann
  hm  : Hamming
  bk  : Blackman
  bh  : Blackman-Haris
```

## option

### option with single argument

- `dt:` time tick of FFT (default is 1.0)
- `fw:` FFT window function
- `gt:` graph type (slope, bin1, bin2) default is slope. see [hplot](hplot.md)
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
- `bp:` set box position, (from 1 to max number of divided frame)

> in `xm:` x margin means distance between maximum/minimum point of data
to left/right edge of x-axis

> in `ym:` y margin means distance between maximum/minimum point of data
to down/up edge of y-axis

### option with two arguments

> arguments is separated by comma with no spaces.

- `xr:` x-axis range (default 0,0 : range is automatically calculated)
- `yr:` x-axis range (default 0,0 : range is automatically calculated)

### option with quoted argument

- `tl:` title (see [title](title.md))
- `xl:` x-label (see [xlab](xlab.md))
- `yl:` y-label (see [ylab](ylab.md))
- `tf:` x-axis time format (see [tfmt](tfmt.md))
- `cc:` cut condition (see [cut](cut.md))

example
```
tip> @ ndata=1000
tip> @ t0=0
tip> @ t1=10
tip> set t=range([ndata],[t0],[t1])

tip> @ pi=3.14159265
tip> @ freq=12
tip> set v=sin([freq]*2*[pi]*t)

tip> div 1 4
tip> plot t v   ;# time domain
tip> fplot t v  ;# freq domain

tip> @ dt=([t1]-[t0])/[ndata]  ;# calculate time tick
tip> fplot v (dt:[dt])         ;# fplot using time tick

tip> ls *_fx,*_fy
v_fx : data(num) : size=512  ;# created data of frequency
v_fy : data(num) : size=512  ;# created data of power spectrum

tip> plot v_fx v_fy            ;# the same as fplot t v
```

for example, see [ex08](../ex/ex08.md), [ex18](../ex/ex18.md)

