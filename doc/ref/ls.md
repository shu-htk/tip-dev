# ls
```
tip> ls
usage: ls pattern
 print list of data or macro variables which matches pattern
 'ls *' show all data or macro variables
```

It shows information of the defined variable which name matches the pattern
for both of data and macro.

If it is data variable, the name and type(num, str, mesh) and it's size is
shown.  
If it is macro variable, the name and type(number, string) and it's value
is shown.

## wild-card matching to the variable name

> wild card is **not the regular expression**  

| match to           | wild card |
|:---:|:---:|
|any string          |  *           |
|any character       |  ?           |
|one of the list of chars|[abc..], [a-z] |

## matching to the list of varable names

> list of ptterns are separated by conmma with no spaces.

| match to           | list of variable name |
|:---:|:---:|
|list of variable names|a,b,c, ... |


example
```
tip> rm *
tip> do n 1 5; set v[n]=[n]; end
tip> for s (a b c); @ x[s]=[s]; end

tip> ls *
xa : string [a]
xb : string [b]
xc : string [c]
v1 : data(num) : size=1
v2 : data(num) : size=1
v3 : data(num) : size=1
v4 : data(num) : size=1
v5 : data(num) : size=1

tip> ls x?
xa : string [a]
xb : string [b]
xc : string [c]

tip> ls v[135]
v1 : data(num) : size=1
v3 : data(num) : size=1
v5 : data(num) : size=1

tip> ls v[2-4],x*
v2 : data(num) : size=1
v3 : data(num) : size=1
v4 : data(num) : size=1
xa : string [a]
xb : string [b]
xc : string [c]
```
