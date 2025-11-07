# print, println, pr, prn
```
tip> print
usage: print args...
       println args...
 print arguments with macro variables format.
                 (see also 'fmt' command)
print  : line is not returned. (abbreviate to 'pr')
print-ln: line is returned. (abbreviate to 'prn')
```

the following escape sequence is available.

|escape char|function|
|:---:|:---:|
| \t | tab |
| \n | return line |

```
tip> print Hello\tWorld\n
Hello  World
```

the quotations is printed as it is.
```
tip> prn You said "Hello World"  ;# prn is abbr. of println 
You said "Hello World"
```

the macro variable is format using [fmt](fmt.md) command.
```
tip> @ e10=exp(10)
tip> prn [e10]
22026.465795

tip> fmt %.3e
tip> prn [e10]
2.203e+04
```
