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

