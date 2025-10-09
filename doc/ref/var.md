# @

```
tip> @
usage: @ x [=|+=|-=|*=|/=] expression
 set the expression value to the macro variable x
```

- spaces between arguments
```
tip> @ x = 1 + 2 ;# OK
tip> @x = 1 + 2  ;# NG you should put space between @ and x
tip> @ x= 1 + 2  ;# OK
tip> @ x=1 + 2   ;# OK
tip> @ x=1+2     ;# OK
```

- define numerical variables
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

using operator "+=" "-=" "*=" "/="
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
```

- define string variable

if left value is not start from digit it is defined as string
```
tip> @ a = Hello
tip> @ b = World!
tip> @ c = [a] [b]
tip> ls *
a : string [Hello]
b : string [World!]
c : string [Hello World!]
```

- some other syntacs
```
tip> @ a = "1"  ;# contents of quatations is string
tip> ls a
a : string [1]
tip>
tip> @ a += "2" ;# append string "2" to the back of string "1"
tip> ls a
a : string [12]
tip> 
tip> @ a += 2   ;# a is coverted to number 12 then added 2
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
tip> @ mass = 1.2kg  ;# this is number ("kg" is removed)
tip> ls mass
mass : number [1.2]
```

- some hacks using macro variable
```
tip> @ kg=e3
tip> @ mass=1.2[kg] ;# this is taken as 1.2e3
tip> prn [mass][g]  ;# [g] is not replaced since it is not defined as variable
1200[g]
tip> @ MHz=e6
tip> @ freq=1.2[MHz] ;# this is taken as 1.2e6
tip> prn [freq][Hz]  ;# [Hz] is not replaced since it is not defined as variable
1200000[Hz]
tip> @ ms=e-3
tip> @ dt=1.2[ms]  ;# this is taken as 1.2e-3
tip> prn [dt][sec] ;# [sec] is not replaced since it is not defined as variable
0.0012[sec]
```
