# fmt
```
usage: fmt ["format"|reset|show]
 specify output format of macro variable.
 (it is same as printf)
 if "reset", it is set to default ("%.11g")
 if "show", print current format
 example: @ x=1; fmt %03.0f; prn [x]
 output:  001
```
