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
tip> div 1 2
tip> set x=range(10,2,20)
tip> plot x (lw:0 st:star sc:red)   ;# single argument
tip> 
tip> set y=exp(0.1*x)
tip> plot x y (lw:0 st:star sc:red) ;# two arguments
```

