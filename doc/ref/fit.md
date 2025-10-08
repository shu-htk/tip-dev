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
