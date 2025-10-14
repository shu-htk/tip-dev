# if, elif, else, fi

```
tip> if
usage: if expr; ...; elif expr; ...; else; ...; fi
```

conditinal branch by evaluating expression

see [logic](logic.md) to learn how the expression evaluated


- example 1
```
do n 1 10
  if [n]<3
    continue
  elif [n]>=8
    break
  else
    prn [n]
  fi
end
```
result
```
3
4
5
6
7
```
- example 2
```
for c (H e l l o W o r l d)
  pr [c]
  if [c]==[A-Z]; pr  : Capital; fi
  pr \n
end
```
result
```
H: Capital
e
l
l
o
W: Capital
o
r
l
d
```
- example 3
```
for name (Greg Anna Ryan Mary Josh)
  pr [name]
  if [name]=={Greg,Ryan,Josh}
    pr  : Boy
  fi
  if [name]=={Anna,Mary}
    pr  : Girl
  fi
  if [name]==A*
    pr  : name begin from 'A'
  fi
  pr \n
end
```
result
```
Greg: Boy
Anna: Girl: name begin from 'A'
Ryan: Boy
Mary: Girl
Josh: Boy
```
