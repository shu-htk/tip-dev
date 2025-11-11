# split
```
tip> split
usage: split s [fs]
 split the string macro variable by delomiter fs
 default delimiter is white space
 splitted string variables are created named s0,..,sN-1
 (N is number of splitted string)
```

exmaple
```
tip> @ s = a b c d
tip> split s          ;# split s by default delimiter (white space)
tip> ls s*
s : string [a b c d]
s0 : string [a]
s1 : string [b]
s2 : string [c]
s3 : string [d]

tip> rm *
tip> @ s = a "b c" d  ;# strings in the quotations are not splitted 
tip> split s
tip> ls s*
s : string [a "b c" d]
s0 : string [a]
s1 : string [b c]
s2 : string [d]

tip> rm *
tip> @ s = a, b, c, d
tip> split s ,         ;# split s by ","
tip> ls s*
s : string [a, b, c, d]
s0 : string [a]
s1 : string [b]
s2 : string [c]
s3 : string [d]

tip> rm *
tip> @ s = a, "b, c", d  ;# strings in the quotations are not splitted 
tip> split s ,
tip> ls s*
s : string [a, "b, c", d]
s0 : string [a]
s1 : string [b, c]
s2 : string [d]
```
