# ++, --

```
tip> ++
usage: ++var
 increment numerical macro variable
```
```
tip> --
usage: --var
 decrement numerical macro variable
```

- example 1
```
tip> @ x=0.1
tip> ls x
x : number [0.1]
tip> ++x
tip> ls x
x : number [1.1]
tip> --x
tip> ls x
x : number [0.1]
```

- example 2
```
tip> @ n=1; for s (a b c); prn [s][n]; ++n; end
a1
b2
c3
```
see also [loop](loop.md)
