# if, elif, else, fi

```
tip> if
usage: if expr; ...; elif expr; ...; else; ...; fi
```

```
$ cat << EOF > a.tip
do n 1 10
  if [n]<3
    continue
   elif [n]>=8
    break
   else
    prn [n]
  fi
end
EOF
```
```
tip> exe a.tip
3
4
5
6
7
```

```
$ cat << EOF > b.tip
for c (H e l l o W o r l d)
  pr [c]
  if [c]==[A-Z]; pr  : Capital; fi
  pr \n
end
EOF
```
```
tip> exe b.tip
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

```
$ cat << EOF > c.tip
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
EOF
```
```
tip> exe c.tip
Greg: Boy
Anna: Girl: name begin from 'A'
Ryan: Boy
Mary: Girl
Josh: Boy
```
