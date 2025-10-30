# ls
```
tip> ls
usage: ls pattern
 print list of both macro and data variables which matches pattern
 'ls *' show all data or macro variables
```

It shows information about both macro variable and data variable
which name matches the pattern.

If it is macro variable, the name and type(number, string) and it's value
is shown.
If it is data variable, the name and type(num, str, mesh) and it's size is
shown.  

## list of variable names

> list of variable names is separated by conmma with no spaces.

## wild-card matching to the variable name

| match to           | wild card |
|:---:|:---:|
|any string          |  *           |
|any character       |  ?           |
|one of the list of chars|[abc..], [a-z] |

> wild card is **not the regular expression**  

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
xa : string [a]
xb : string [b]
xc : string [c]
v2 : data(num) : size=1
v3 : data(num) : size=1
v4 : data(num) : size=1
```
