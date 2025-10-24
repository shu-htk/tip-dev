# elem
```
usage: elem x = v(N)
 copy Nth element of data v to the macro variable x.
 (N begin from 0)
```

example
```
tip> set v = range(11,0,1)
tip> cat v (fs:"\n")
v : data(num) :
0
0.1
0.2
0.3
0.4
0.5
0.6
0.7
0.8
0.9
1

tip> elem x = v(3)
tip> ls x
x : number [0.3]

tip> elem x = v(20)
index 20 is out of range

tip> do n 0 10; elem x=v([n]); prn element of v([n]) is [x]; end
element of v(0) is 0
element of v(1) is 0.1
element of v(2) is 0.2
element of v(3) is 0.3
element of v(4) is 0.4
element of v(5) is 0.5
element of v(6) is 0.6
element of v(7) is 0.7
element of v(8) is 0.8
element of v(9) is 0.9
element of v(10) is 1
```
