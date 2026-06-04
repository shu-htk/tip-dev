# legend
```
Usage: legend [command] [(opt)]
Draw legend on the existing graph. (alias: leg)
command:
 show [xpos,ypos]
   xpos: right(r), middle(m), left(l) : (default is right)
   ypos: top(t), middle(m), bottom(b) : (default is top)
 ls
   list legend strings.
 rm
   remove legend strings.
Example:
  plot x y (st:plus lg:*)
  legent show l,m
 draws plus marker '+' and text 'x : y' at left,middle of the grapgh
```
