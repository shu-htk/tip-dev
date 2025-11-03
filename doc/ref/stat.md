# stat
```
tip> stat
usage: stat v [(opt)]
 make the statistics information of data v.
 the macro variables [v_max] [v_min] [v_mean] [v_rms]
 and [v_entry] are created.
 if option 'cp:' is specified they are drawn in the current graph.
```

example
```
tip> @ sigma=3
tip> @ mean=5
tip> set x=random(10000,gaus,[sigma],[mean])

tip> stat x
@ Statistics:
 entry=10000
 max= 16.644
 min= -6.43861
 mean= 4.99203
 rms= 2.98497

tip> ls x_*
x_entry : number [10000]
x_max : number [16.643976249]
x_mean : number [4.9920299184]
x_min : number [-6.438606022]
x_rms : number [2.9849657177]
```

for more example, see [ex19](../ex/ex19.md)
