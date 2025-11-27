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

### option with two arguments

> arguments is separated by comma with no spaces.

- `nr:` set data range of output (1st data is begin from 1)

> if `nr:` is not specified (default `nr:0,-1`), all data is outputted  
> if `nr:N,-1`, it it outputted from N to end

### option with quoted argument

- `fs:` set field separator of output (console only)

example using `fs:`, `nr:`
```
tip> set x=range(5, 0.1, 0.5)
tip> cat x
x : data(num) :  0.1 0.2 0.3 0.4 0.5

tip> cat x (fs:"\n")
x : data(num) :
0.1
0.2
0.3
0.4
0.5

tip> cat x (fs:"\n" nr:2,4)    ;# output from 2nd to 4th data 
x : data(num) :
0.2
0.3
0.4

tip> cat x (fs:"\n" nr:2,-1)   ;# output from 2nd to end
x : data(num) :
0.2
0.3
0.4
0.5
```

example of concatenating data
```
tip> set x1={1,2,3}
tip> set x2={4,5,6}
tip> cat x?
x1 : data(num) :  1 2 3
x2 : data(num) :  4 5 6

tip> cat x1,x2 > x3  ;# redirected to x3
tip> cat x3
x3 : data(num) :  1 2 3 4 5 6

tip> cat x1,x2 >> x3  ;# appended to x3
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


