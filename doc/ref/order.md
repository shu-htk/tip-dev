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

> Available in version **v1.2.2** and later
