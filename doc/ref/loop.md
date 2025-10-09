# for, do, while, end

```
tip> for
usage: for s (a b ...); ...; end
```

```
tip> do
usage: do n N1 N2 [dN]; ...; end
```

```
tip> while
usage: while expr; ...; end
```

- example of for
```
tip> for func (sin cos)
loop>  @ x=[func](1)      ;# prompt changed to "loop>" until "end" 
loop>  prn [func](1)=[x]
loop> end
sin(1)=0.84147098481
cos(1)=0.54030230587
tip> 
```

- example of do
```
tip> do x 0 1 0.3
loop>  prn [x]
loop> end
0
0.3
0.6
0.9
tip> do x 1 0 -0.3; prn [x]; end   ;# write it in one line
1
0.7
0.4
0.1
```

- example of while
```
tip> @ n=1
tip> while [n]<5
loop>  prn [n]
loop>  ++n
loop> end
1
2
3
4
tip> @ n=5; while [n]>0; prn [n]; --n; end
5
4
3
2
1
```
see also [logic](logic.md)
