# for, do, while, end

## usage

- **for-loop**
```
tip> for
usage: for s (a b ...); ...; end
```
It is assigned for each value listed in the brackets ( )
to the macro variable 's'.  

- **do-loop**
```
tip> do
usage: do n N1 N2 [dN]; ...; end
```
It is assigned numerical value which range is from N1 to N2 incremented dN
to the macro variable 'n'.  
The value can take floating point number.
If dN is not specified, it is incremented +1  

- **while-loop**
```
tip> while
usage: while expr; ...; end
```
It is evaluated the [logical expression](logic.md) for each time,
if it is is true continue, if false break.

## example

- **for-loop**
```
for func (sin cos exp)
  for x (1 2)
    @ y = [func]([x])
    prn [func]([x]) = [y]
  end
end
```
result
```
sin(1) = 0.84147098481
sin(2) = 0.90929742683
cos(1) = 0.54030230587
cos(2) = -0.41614683655
exp(1) = 2.7182818285
exp(2) = 7.3890560989
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

