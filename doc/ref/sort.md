# sort
```
tip> sort
Usage: sort v1,v2,... by v
Sort v1,v2,... in ascending order using v.
Creates v1_sort, v2_sort, ...
```
> argument list of variable names is separated by comma with no spaces.

example
```
tip> set x={3,1,7,9,5}
tip> set s={d,e,a,b,c}
tip> cat x,s
x : data(num) :  3 1 7 9 5
s : data(str) :  d e a b c

tip> sort x,s by x
tip> cat x_sort,s_sort
x_sort : data(num) :  1 3 5 7 9
s_sort : data(str) :  e d c a b

tip> sort x,s by s
tip> cat x_sort,s_sort
x_sort : data(num) :  7 9 5 3 1
s_sort : data(str) :  a b c d e
```
