# random

```
tip> random
usage: set v = random(N,uni[,x0,x1]) [(opt)]
       set v = random(N,gaus[,sgm,mean]) [(opt)]
       set v = random(N,exp[,tau]) [(opt)]
 set random numbers to the data v which size N.
  uni,x0,x1 : uniform distribution [x0:x1] (default x0=0,x1=1)
  gaus,sgm,mean : gauss distribution (default sgm=1,mean=0)
  exp,tau   : exponential distribution (default tau=1)
 option:
  sd:n   : set integer value n as random seed
  sd:utime : set unix time(sec) as random seed
  sd:clock : set clock(nsec) as random seed (this is default)
```

## option

- `sd:` set integer value as a random seed  
>  if value is "utime" set unix epoch time(sec)  
>  if value is "clock" set computer clock(nsec)

## Uniform distribution

uniform random number in the range [x0,x1]

## Gaussian distribution  (Box-Muller transform Method)

_sigma \* sqrt(-2\*log(a)) \* sin(2\*PI\*b) + mean_ 
&emsp; : a,b is independent uniform_

## Exponential distribution (Inverse Transform Method)

if tau>0 ;&emsp; _-log(a) / tau_  &emsp; : a is uniform (0,1]  
if tau<0 ;&emsp; _log(a) / tau_   &emsp; : a is uniform(0,1]  
if tau=0 ;&emsp; _1_


