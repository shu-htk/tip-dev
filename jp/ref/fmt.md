# fmt
```
tip> fmt
Usage: fmt ["format" | reset | show]
Specify the output format for macro variables.
(Same syntax as printf.)
reset : restore the default format ("%.11g")
show  : display the current format
Example:
  @ x=1; fmt "%03.0f"; prn [x]
Output:
  001
```

format specifiers

|specifier| |
|:---:|:---:|
| %f | OK |
| %e | OK |
| %g | OK |
| %c | N/A |
| %s | N/A |
| %d | N/A |
| %u | N/A |
| %x | N/A |

```
tip> @ e=exp(1)
tip> prn [e]
2.7182818285

tip> fmt %.3f
tip> prn [e]
2.718

tip> fmt reset
tip> fmt show
[%.11g]
```

```
tip> fmt %03d     ;# this is NG
invalid format [%03d]
since numerical variable type is 'double'
you should specify the format 'f' or 'e' or 'g'
tip>
tip> fmt %03.0f   ;# this is OK
tip> do n 1 10; @ filename=test[n].dat; prn [filename]; end
test001.dat
test002.dat
test003.dat
test004.dat
test005.dat
test006.dat
test007.dat
test008.dat
test009.dat
test010.dat
```
