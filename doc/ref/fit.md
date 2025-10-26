# fit
```
usage: fit x y [lin|quad|exp|log|gaus|sin|circ] [(opt)]
 do fitting to the data x and y and draw the result.
 you should do 'plot x y' before this command.
 available fitting functions:
   l[in] : y = c0 + c1*x 
   q[uad]: y = c0 + c1*x + c2*x^2 
   e[xp] : y = c0*exp(c1*x) 
   log   : y = c0 + log(c1*x) 
   g[aus]: y = c0*exp(-(x-c1)^2/2*c2^2) 
   s[in] : y = c0 + c1*sin(2*PI*c3*x) + c2*cos(2*PI*c3*x) 
   c[irc]: (x-c0)**2 + (y-c1)**2 = c2**2 
```

do fitting to the curve of data x and y after [plot](plot.md) command

## fitting functions

|name | abbr. | expression |
|:---:|:---:|:---:|
|lin  | l | ey = c0 + c1*x | 
|quad | q | y = c0 + c1*x + c2*x^2 | 
|exp  | e | y = c0*exp(c1*x) |
|log  |log| y = c0 + log(c1*x) | 
|gaus | g | y = c0*exp(-(x-c1)^2/2*c2^2) | 
|sin  | s | y = c0 + c1*sin(2*PI*c3*x) + c2*cos(2*PI*c3*x) | 
|circ | c | (x-c0)**2 + (y-c1)**2 = c2**2 |

## option

- lc: line color of fitted curve
- lt: line style of fitted curve
- cp: comment position of fitting information
- rc: flag to set relative coordinate for comment position

see [ex7a](../ex/ex07a.md), [ex7a](../ex/ex07b.md)
