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

- example of for loop
```
tip> for func (sin cos)
loop>  @ x=[func](1)      ;# prompt changed to "loop>" until "end" 
loop>  prn [func](1)=[x]
loop> end
sin(1)=0.84147098481
cos(1)=0.54030230587
tip> 
```

- example of do loop

incremental loop with continue and break
```
tip> do n 0 10
loop> if 1<[n]<5; continue; fi
loop> if [n]>7; break; fi
loop> prn [n]
loop> end
0
1
5
6
7
```
see also [if,fi](if_fi.md) and [logic](logic.md)

decremental loop
```
tip> do x 1 0 -0.3; prn [x]; end   ;# write it in one line
1
0.7
0.4
0.1
```

- example of while loop
```
tip> @ n=0
tip> @ s=a
tip> while [s]!=aaaa
loop>  if [n]>100; break; fi  ;# in case bad condition, avoid infinity loop
loop>  prn [s]
loop>  @ s=[s]a
loop> end
a
aa
aaa
```
see also [if,fi](if_fi.md) and [logic](logic.md)
