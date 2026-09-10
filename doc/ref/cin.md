# cin
```
tip> cin
Usage: cin v [prompt]
Input expression from console to macro variable v.
```
> Available in version v1.2.5 and later

example
```
tip> cin x  ;# default prompt is "cin"
cin > 0.7
tip> ls x
x : number [0.7]

tip> cin x "input numerical expression"
input numerical expression > sin(1)+cos(1)
tip> ls x
x : number [1.3817732907]

tip> cin s "input string"
input string > a b c
tip> ls s
s : string [a b c]

tip> cin s2 "input string"
input string > [s]
tip> ls s2   ;# [s] is not expanded to "a b c"
s2 : string [[s]]
```
