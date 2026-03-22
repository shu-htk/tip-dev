# split
```
tip> split
Usage: split s [fs]
Split the string macro variable s using delimiter fs.
If fs is omitted, whitespace is used.
The results are stored in s1, s2, ..., sN
(N is the number of split elements.)
```

exmaple
```
tip> @ s = a b c d
tip> split s          ;# split s by default delimiter (white space)
tip> ls s*
s : string [a b c d]
s1 : string [a]
s2 : string [b]
s3 : string [c]
s4 : string [d]

tip> rm *
tip> @ s = a "b c" d  ;# strings in the quotations are not splitted 
tip> split s
tip> ls s*
s : string [a "b c" d]
s1 : string [a]
s2 : string [b c]
s3 : string [d]

tip> rm *
tip> @ s = a, b, c, d
tip> split s ,         ;# split s by ","
tip> ls s*
s : string [a, b, c, d]
s1 : string [a]
s2 : string [b]
s3 : string [c]
s4 : string [d]

tip> rm *
tip> @ s = a, "b, c", d  ;# strings in the quotations are not splitted 
tip> split s ,
tip> ls s*
s : string [a, "b, c", d]
s1 : string [a]
s2 : string [b, c]
s3 : string [d]
```
