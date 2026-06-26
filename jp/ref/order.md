# order
```
tip> order
Usage: order [color] [color1,color2,...| off | default | ls]
       order [symbol] [symb1,symb2,... | off | default | ls]
       order [fill]   [fill1,fill2,... | off | default | ls]
Set order of colors/symbols/fills list.
Special list name:
  off : clear the list.
  default : set the default list.
  ls : show the current list.
Example:
  order color red,blue
  plot x y1
  plot x y2
  plot x y3
In this case, y1 is drawn with red, y2 is drawn with blue,
and y3 is drawn with red again.
```

> **v1.2.2** 以降から使える

example
```
tip> set x=range(10,1,10)
tip> set y=log(x)

tip> order color default  ;# set default color list
tip> order color ls
red blue green cyan pink wheat brown violet

tip> plot x y   ;# plot with red
tip> plot x y   ;# plot with blue
tip> plot x y   ;# plot with green
tip> plot x y   ;# plot with cyan
tip> plot x y   ;# plot with pink
tip> plot x y   ;# plot with wheat
tip> plot x y   ;# plot with brown
tip> plot x y   ;# plot with violet
tip> plot x y   ;# plot with red again

tip> order color yellow,aqua,magenta  ;# set user defined color list
tip> order color ls
yellow aqua magenta

tip> plot x y   ;# plot with yellow
tip> plot x y   ;# plot with aqua
tip> plot x y   ;# plot with magenta
tip> plot x y   ;# plot with yellow again

tip> order color off  ;# automatic color change is off

tip> plot x y   ;# plot with black
```
