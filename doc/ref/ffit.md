# ffit
```
usage: ffit v [func] [(opt)]
 you should do the 'fplot' before this command.
 then 'fit v_fx v_fy [func]' is done.
 see the command 'fit' for the fitting functions.
```

do fitting to the curve of frequency domain after [fplot](../ref/fplot.md).

- v is time domain data

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

see [ex18](../ex/ex18.md)

