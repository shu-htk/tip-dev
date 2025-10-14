# print
```
usage: print args...
       println args...
 print arguments with macro variables formated.
                 (see also 'fmt' command)
print  : line is not returned. (abbreviate to 'pr')
println: line is returned. (abbreviate to 'prn')
```

the following escape sequence is available.

|escape char|function|
|-|-|
| \t | tab |
| \r | return line |

the quotations is printed as it is.

```
tip> print Hello\tWorld\n
Hello  World

tip> prn You said "Hello World"
You said "Hello World"
```

the macro variable is formated using [fmt](fmt.md) command.
```
tip> @ e10=exp(10)
tip> prn [e10]
22026.465795

tip> fmt %.3e
tip> prn [e10]
2.203e+04
```

```
tip> fmt %03d
invalid format [%03d]
since numerical variable type is 'double'
you should specify the format 'f' or 'e' or 'g'
```
