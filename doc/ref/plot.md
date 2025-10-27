# plot
```
usage: plot [x] y [(opt)]
 plot the 2D-graph of data x and y.
 if data x is not specified the index data 'y_n' is created
 then 'plot y_n y' is done.
```

## option

- lc: line color of fitted curve
- lt: line style of fitted curve
- cp: comment position of fitting information
- rc: flag to set relative coordinate for comment position

example

```
@ pi2=3.14159265*2
set t=range(50,0,[pi2])
set v=sin(t)

opt (gd:1 lw:0 st:pls sc:red)
div 1 2

title "Index vs Value of data v"
plot v   ;# index data 'v_n' is automatically generated

title "Value of data t vs v"
plot t v
```

