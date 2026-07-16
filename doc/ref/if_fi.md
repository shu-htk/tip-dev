# if, elif, else, fi

```
tip> if
usage: if expr; ...; elif expr; ...; else; ...; fi
```

conditional branch by evaluating logical expression

see [logic](logic.md) to learn how the logical expression evaluated


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
