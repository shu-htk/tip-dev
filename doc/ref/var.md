# @

```
tip> @
usage: @ x [=|+=|-=|*=|/=|%=] expression
usage: @ t = time(s[,unit])
 set the expression value to the macro variable x
 convert ISO time string to unix epoch time and vice versa
```
see [calc](calc.md) to learn how expression is calulated

## spaces between arguments
```
tip> @ x = 1 + 2 ;# OK
tip> @x = 1 + 2  ;# NG you should put space between @ and x
tip> @ x= 1 + 2  ;# OK
tip> @ x=1 + 2   ;# OK
tip> @ x=1+2     ;# OK
```

## numerical macro variables
```
tip> @ pi=3.14159265
tip> @ x=sin([pi]/2)
tip> ls *
pi : number [3.14159265]
x : number [1]
tip>
tip> prn sin([pi]/2)=[x]  ;# prn is abbr. of println
sin(3.14159265/2)=1
tip>
tip> fmt "%.2f"  ;# set format of [pi] and [x]
tip> prn sin([pi]/2)=[x]
sin(3.14/2)=1.00
```
see also [print](print.md) and [fmt](fmt.md)

using operator `+=`  `-=`  `*=`  `/=` `%=`
```
tip> @ x = 1.23
tip> prn [x]
1.23
tip> @ x += 1/10  ;# 1/10 is calculated to 0.1
tip> prn [x]
1.33
tip> @ x -= 1
tip> prn [x]
0.33
tip> @ x *= 2
tip> prn [x]
0.66
tip> @ x /= 3
tip> prn [x]
0.22
tip> @ x %= 0.1  ;# x = fmod(x,0.1)
tip> prn [x]
0.02
```

## string macro variable

if expression is not starting from digit it is defined as string
```
tip> @ a = Hello
tip> @ b = World!
tip> @ c = [a] [b]
tip> ls *
a : string [Hello]
b : string [World!]
c : string [Hello World!]
```

## ternary operator
**note)**
> ternary operator can not be nested
```
tip> @ x=7
tip> @ size = [x]>5 ? L : S          ;# this is OK
tip> ls size
size : string [L]
tip> 
tip> @ size = [x]>4 ? ([x]>7 ? L : M ) : S  ;# NG it can't be nested
Var::parse_ternary(): operator lack of args
```

## some other syntax

```
tip> @ a = "1"  ;# enclosing the expr by quotations, it is treated as string
tip> ls a
a : string [1]
tip>
tip> @ a += "2" ;# append string "2" to the back of string "1"
tip> ls a
a : string [12]
tip> 
tip> @ a += 2   ;# a is converted to number 12 then added 2
tip> ls a
a : number [14]
tip>
tip> @ a -= "2"
invalid operator of string
tip> @ a *= "2"
invalid operator of string
tip> @ a /= "2"
invalid operator of string
tip>
tip> @ m = 1.2kg  ;# this is number ("kg" is removed)
tip> ls m
m : number [1.2]
```

hacks to put the metric prefix using macro variable
```
tip> @ kg=e3
tip> @ m=1.2[kg]        ;# 1.2[kg] is replaced to 1.2e3
tip> prn mass=[m][g]    ;# [g] is not replaced since it is not defined
mass=1200[g]
```

## convert ISO time string to unix epoch time and vice versa

```
tip> @ t=time("2001-02-03 09:12:37.0") ;# ISO-time-string to unix-epoch-time
tip> ls t
t : number [981191557]

tip> @ ts=time([t],str)                ;# unix-epoch-time to ISO-time-string
tip> ls ts
ts : string [2001-02-03 09:12:37.000000]
```
