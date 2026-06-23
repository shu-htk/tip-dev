# order
```
ip> order
Usage: order [color]  [color1,color2,... | off]
       order [symbol] [symb1,symb2,... | off]
       order [fill]   [fill1,fill2,... | off]
       order [ls | def | reset]
Set order of colors/symbols/fills list.
'ls' shows current lists of order.
'def' set default lists of order.
'reset' clears all lists.
Example:
  order color red,blue
  plot x y1
  plot x y2
  plot x y3
In this case, y1 is drawn with red, y2 is drawn with blue,
and y3 is drawn with red again.
```

> **v1.2.2** 以降から使える

