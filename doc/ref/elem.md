# elem
```
tip> elem
usage: elem x = v(N)
 copy Nth element of data v to the macro variable x.
 (N begin from 0)
```

**note)**
> unlike option `nr:` index of element begin from 0

see also [cat](cat.md)

example
```
tip> set x=range(5, 0.1, 0.5)
tip> cat x (fs:"\n")
x : data(num) :
0.1
0.2
0.3
0.4
0.5
tip> elem v = x(3)   ;# since index begin from 0, x(3) is 4th data
tip> ls v
v : number [0.4]

tip> elem v = x(20)
index 20 is out of range

tip> do n 0 4; elem v=x([n]); prn element of x([n]) is [v]; end
element of x(0) is 0.1
element of x(1) is 0.2
element of x(2) is 0.3
element of x(3) is 0.4
element of x(4) is 0.5
```
