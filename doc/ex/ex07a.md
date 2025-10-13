# ex07a: Fitting Linear/Quadratic/Gaussian
```
opt (gd:1 lw:0 lc:green st:dot rc:1)
viewport 0.15 0.97 0.15 0.9 0.72

fmt %.6f
@ ndata = 1000 ; # number of data
@ sigm = 0.05  ; # sigma of random gaussian
set bg = random([ndata],gaus,[sigm]) ; # background noise (random gaussian)

div 2 2

title "Linear Fitting" ;#------------------------------------------------
@ p0 = 0.1
@ p1 = 0.8
set x = range([ndata],-1,1)
set y = [p0] + [p1]*x + bg
plot x y
fit x y lin (cp:0.1,0.8 ts:0.8 cf:c)
print input  p0=[p0] p1=[p1]\n
print fitted c0=[c0] c1=[c1]\n

title "Quadratic Fitting" ;#------------------------------------------------
@ p0 = 0.3
@ p1 = 0.4
@ p2 = 0.5
set x = range([ndata],-1,2)
set y = [p0] + [p1]*x + [p2]*x*x + bg
plot x y
fit x y quad (cp:0.1,0.8 ts:0.8 cf:c)
print input  p0=[p0] p1=[p1] p2=[p2]\n
print fitted c0=[c0] c1=[c1] c2=[c2]\n

title "Gaussian Fitting" ;#------------------------------------------------
@ p0 = 2.1
@ p1 = -0.5
@ p2 = 1.1
set x = range([ndata],-3,6)
set y = [p0] * exp(-(x-[p1])*(x-[p1])/([p2]*[p2]*2.0)) + bg
plot x y
fit x y gaus (cp:0.45,0.9 ts:0.8 cf:c)
print input  p0=[p0] p1=[p1] p2=[p2]\n
print fitted c0=[c0] c1=[c1] c2=[c2]\n

title "Gaussian Fitting of small data" ;#---------------------------------
set x = {0.8, 0.9, 1.0, 1.1, 1.2}
set y = {0.9, 1.05, 1.08, 0.95, 0.8}
plot x y (st:star lw:0)
fit x y gaus (cp:0.2,0.5 ts:0.8)
```
![](../fig/ex07a.png)
