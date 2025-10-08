# cut
```
usage: cut v1,v2,... "expression"
 where v1,v2,... are data to cut
 new data v1_cut,v2_cut,... are created
example:
 cut x,y "0<x<1 & 1<y<2"
 plot x_cut y_cut
using option 'cc:' it is also done by
 plot x y (cc:"0<x<1 & 1<y<2")
```
