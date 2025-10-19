# for, do, while, end

## usage

- **for-loop**
```
tip> for
usage: for s (a b ...); ...; end
```
it is assigned for each value listed in the brackets ( )
to the macro variable 's'.  
the value is assigned as string even if it is digit

- **do-loop**
```
tip> do
usage: do n N1 N2 [dN]; ...; end
```
it is assigned numerical value which range is from N1 to N2 incremented dN
to the macro variable 'n'.  
the value can take floating point number.
if dN is not specified, it is incremented +1  

- **while-loop**
```
tip> while
usage: while expr; ...; end
```
the [logic](logic.md) expression is evaluated for each loop,
if it is is true continue the loop,
if it is false break the loop.

## example

- **for-loop**
```
for func (sin cos)
  @ x=[func](1)
  prn [func](1)=[x]
end
```
result
```
sin(1)=0.84147098481
cos(1)=0.54030230587
```

- **do-loop**

incremental loop with continue and break
```
do n 0 10
  if 1<[n]<5; continue; fi
  if [n]>7; break; fi
  prn [n]
end
```
result
```
0
1
5
6
7
```
decremental loop
```
do x 1 0 -0.3; prn [x]; end
```
result
```
1
0.7
0.4
0.1
```

- **while-loop**
```
@ n=0
@ s=a
while [s] != aaaa
  prn [n] [s]
  @ s += a   ;# equivalent to @ s = [s]a
  ++n
  if [n]>100; break; fi  ;# to avoid infinity loop in case bad condition
end
```
result
```
0 a
1 aa
2 aaa
```
see also [if,fi](if_fi.md) and [logic](logic.md)

