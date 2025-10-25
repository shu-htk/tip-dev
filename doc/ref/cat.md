# cat
```
tip> cat
usage: cat v1,v2,... [>|>>] [v] [(opt)]
 concatenate data v1,v2,.. and print contents
 redirect to the data v:
   >  : over write
   >> : append
 option:
   nr:N0,N1 : choose index number range from N0 to N1
```
## option

- `fs:` set field separater of console output
- `nr:` set index range of cosole output

example
```
tip> set x=range(10,0,9)
tip> cat x
x : data(num) :  0 1 2 3 4 5 6 7 8 9

tip> cat x (fs:",")
x : data(num) : 0,1,2,3,4,5,6,7,8,9

tip> cat x (fs:"\n")
x : data(num) :
0
1
2
3
4
5
6
7
8
9

tip> cat x (nr:2,8)
x : data(num) :  2 3 4 5 6 7
```

```
tip> set x1={1,2,3}
tip> set x2={4,5,6}
tip> cat x?
x1 : data(num) :  1 2 3
x2 : data(num) :  4 5 6

tip> cat x1,x2 > x3  ;# redirected to x3
tip> cat x3
x3 : data(num) :  1 2 3 4 5 6

tip> cat x1,x2 >> x3  ;# apended to x3
tip> cat x3
x3 : data(num) :  1 2 3 4 5 6 1 2 3 4 5 6

tip> cat x2,x1 > x3 ;# order of x1 and x2 is swapped
tip> cat x3
x3 : data(num) :  4 5 6 1 2 3
```

```
tip> set x1={1,2,3}
tip> set x2={a,b,c}
tip> set x3={4,5,6}
tip> cat x?
x1 : data(num) :  1 2 3
x2 : data(str) :  a b c
x3 : data(num) :  4 5 6

tip> cat x1,x2,x3 > x4
incompatible type [str]!=[num] skipped.
tip> cat x4
x4 : data(num) :  1 2 3 4 5 6

tip> cat x2,x1,x3 > x4
incompatible type [num]!=[str] skipped.
incompatible type [num]!=[str] skipped.
tip> cat x4
x4 : data(str) :  a b c
```


