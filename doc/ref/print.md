# print, println, pr, prn
```
tip> print
Usage: print args...
       println args...
Print the given arguments.
(See also the 'fmt' command.)
print   : does not append a newline (alias: pr)
println : appends a newline (alias: prn)
```

escape sequence

|escape char|function|
|:---:|:---:|
| `\t` | tab |
| `\n` | return line |

```
tip> print Hello\tWorld\n
Hello  World
```

the quotations are printed as they are.
```
tip> prn You said "Hello World"  ;# prn is abbr. of println 
You said "Hello World"
```

the value of the macro variable is formated using [fmt](fmt.md) command.
```
tip> @ e10=exp(10)
tip> prn [e10]
22026.465795

tip> fmt %.3e
tip> prn [e10]
2.203e+04
```
