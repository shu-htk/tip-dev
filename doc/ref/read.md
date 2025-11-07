# read
```
tip> read
usage: read v1,v2,... file_name [(opt)]
       read v1,v2,... `command` [(opt)]
 where v1,v2,... are list of data to read
 if `command` specified instead of file_name,
 data are read from the out put of the system command
```

## option

### option with two arguments

> arguments is separated by comma with no spaces.

- `nr:` set range of line number to read (1st line is begin from 1)

### option with quoted argument by ""

- `fs:` field separator

## file format

data file is multi column text separated by field separator.
The default field separator is a space character.

in the case the number of column is M,

| v1  | v2  | ... | vM  |
|:---:|:---:|:---:|:---:|
|v1(1)|v2(1)| ... |vM(1)|
|v1(2)|v2(2)| ... |vM(2)|
| ... | ... | ... | ... |


## naming rule of valiable list

If it is specified a list of N variables, and file has M columns,

```
 read v1,v2,...,vN  file_of_M_column.dat
```

- if N < M, last n columns are named as vN1, ... , vNn (n=M-N+1)
- if N > M, vn, ... , VN are ignored (n=M+1)

## read the output of the system command

> If the filename is a command enclosed in backquotes,
> its output is read through the pipe.

example,
```
tip> set id={1,2,3,4,5}
tip> set name={A,B,C,D,E}
tip> set val1={11,21,31,41,51}
tip> set val2={12,22,32,42,52}
tip> set val3={13,23,33,43,53}
tip> cat id,name,val*
id : data(num) :  1 2 3 4 5
name : data(str) :  A B C D E
val1 : data(num) :  11 21 31 41 51
val2 : data(num) :  12 22 32 42 52
val3 : data(num) :  13 23 33 43 53

tip> write id,name,val* test.dat  ;# save variables to the file
tip> rm *  ;# remove all variables

tip> read x test.dat  ;# xn (n=1,2,3,4,5) are created
tip> cat x*
x1 : data(num) :  1 2 3 4 5
x2 : data(str) :  A B C D E
x3 : data(num) :  11 21 31 41 51
x4 : data(num) :  12 22 32 42 52
x5 : data(num) :  13 23 33 43 53

tip> read a,b,c,d,e,f test.dat  ;# f is ignored
tip> cat [a-f]
a : data(num) :  1 2 3 4 5
b : data(str) :  A B C D E
c : data(num) :  11 21 31 41 51
d : data(num) :  12 22 32 42 52
e : data(num) :  13 23 33 43 53

tip> read id,name,v test.dat   ;# vn (n=1,2,3) are created
tip> cat id,name,v*
id : data(num) :  1 2 3 4 5
name : data(str) :  A B C D E
v1 : data(num) :  11 21 31 41 51
v2 : data(num) :  12 22 32 42 52
v3 : data(num) :  13 23 33 43 53

tip> read x `tail -3 test.dat`  ;# read the output of the system command
tip> cat x*
x1 : data(num) :  3 4 5
x2 : data(str) :  C D E
x3 : data(num) :  31 41 51
x4 : data(num) :  32 42 52
x5 : data(num) :  33 43 53

tip> read x test.dat (nr:2,4)   ;# read line which number is from 2 to 4
tip> cat x*
x1 : data(num) :  2 3 4
x2 : data(str) :  B C D
x3 : data(num) :  21 31 41
x4 : data(num) :  22 32 42
x5 : data(num) :  23 33 43
```


