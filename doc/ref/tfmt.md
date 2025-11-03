# tfmt
```
tip> tfmt
usage: tfmt "time format"
       tfmt reset
 set x-axis time format.
 equivalent to 'opt (tf:"time format")'
 tags in the format:
         %Y(year), %m(month), %d(day), %H(hour), %M(min), %S(sec)
 reset : x-axis is reset to normal format.
 ```

this command is equivalent to `opt (tf:"time format")`

example
```
opt (td:"/ :")  ;# set time delimiters of ISO time format

@ T1=time("2001/01/01 00:00:00")
@ T2=time("2001/01/02 00:00:00")
@ T3=time("2011/12/31 00:00:00")

set t12=range(100,[T1],[T2])
set v12=random(100,exp)

set t13=range(100,[T1],[T3])
set v13=random(100,exp)

div 1 2
tfmt "%m/%d %H:%M"
plot t12 v12 (xl:"month/day hour:min")

tfmt "%Y/%m/%d"
plot t13 v13 (xl:"year/month/day")
```
