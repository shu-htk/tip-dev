# elem
```
tip> elem
usage: elem x = v(N)
 copy Nth element of data v to the macro variable x.
 (N begin from 1)
```
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
tip> elem v = x(3)
tip> ls v
v : number [0.3]

tip> elem v = x(20)
index 20 is out of range

tip> do n 1 5; elem v=x([n]); prn element of x([n]) is [v]; end
element of x(1) is 0.1
element of x(2) is 0.2
element of x(3) is 0.3
element of x(4) is 0.4
element of x(5) is 0.5
```
