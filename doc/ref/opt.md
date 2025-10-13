# opt

## usage
```
usage: opt (item1:value1 item2:value2 ...)
     : opt item1 item2 ...
     : opt color|line|symbol|fill|reset
set or show the global options
 if items are in the bracket (), the item values are set
 if not in (), the item values are shown
 if item is '*', all of the item names and values are shown
 others,
  color(c)  : show list of the color names
  line(l)   : show list of the line-style names
  symbol(s) : show list of the symbol names
  fill(f)   : show list of the fill-area-style names
  reset     : set the default value for all items
```

- **global option and local option**
```
tip> opt (lc:red)       ;# set the global line color red
tip> plot x y           ;# the line color is red
tip> plot x y (lc:blue) ;# the line color is blue
tip> plot x y           ;# the line color is red
tip> opt reset          ;# reset global options
tip> plot x y           ;# the line color is black (default color)
```

## list of options

conventionally tip uses "2-letters option".

```
tip> opt *
ae: arrow edge(0=non,1=end,2=begin,3=both): [0]
al: altitude: [45]
az: azimuth: [45]
bo: box drawing order : [0]
bp: box position : [0]
cc: cut condition: []
cf: tag of fit.coeff: []
cp: comment position: [0,0]
cr: clear flag : [1]
dm: debug mode : [0]
dt: time tick of FFT: [1]
fc: fill area color: [white]
fl: flush flag: [1]
fq: freq of sin.fit: [1]
fr: fitting range: [0,0]
fs: field separator : [white space]
ft: fill area style: [null]
fw: FFT window func (rc,hn,hm,bk,bh): [rc]
gc: gradient of contour : [32]
gd: grid flag : [0]
gt: graph type (slope,bin1,bin2): [slope]
ht: histogram type (bin1,bin2,slope): [bin1]
lc: line color : [black]
lt: line style : [solid]
lw: line width : [1]
mt: mesh graph type (mesh1,mesh2,cont1,cont2): [mesh1]
mv: moving average number: [1]
nb: histogram bin: [100]
nf: take null field: [0]
nr: numbers range: [0,0]
nx: 2D-histogram xbin: [20]
ny: 2D-histogram ybin: [20]
rc: relative coordinate flag: [0]
rp: replot flag: [0]
sc: symbol color: [black]
sd: random seed: [clock]
st: symbol type : [non]
ss: symbol size : [1]
tc: text color : [black]
td: time-format-delimiters : [- :]
tf: x-axis time format: []
tl: graph title : []
tp: text pos(0:L to 1:R) : [0]
tr: text rotation(deg) : [0]
ts: text size : [1]
xl: x-axis label: []
xm: x margin factor: [0.02]
xn: x-subtick num: [0]
xr: x-axis range: [0,0]
xs: x-axis scale: [lin]
xt: x-tick interval: [0]
yl: y-axis label: []
ym: y margin factor: [0.1]
yn: y-subtick num: [0]
ys: y-axis scale: [lin]
yt: y-tick interval: [0]
yr: y-axis range: [0,0]
zl: z-axis label: []
zm: z margin factor: [0.1]
zr: z-axis range: [0,0]
```
