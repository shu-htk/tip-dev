# time

```
tip> time
usage: set vn = time([vn|vs][,unit])
usage: set vs = time([vn|vs],str)
 convert the time data
 vs is the string data of ISO time-format.
 vn is numerical data of unix-epoch time.
 if 1st argument is "now" it returns the current local time
 unit:
   utime : return unix-epoch time in usec precision (UTC)
   year  : return years with decimal (local time)
   mon   : return months with decimal (local time)
   day   : return days with decimal (local time)
   hour  : return hours with decimal (local time)
   min   : return minutes with decimal (local time)
   sec   : return seconds with decimal (local time)
   usec  : return micro-seconds
   str   : return ISO time format string (local time)
                  like "Year-Mon-Day Hour:Min:Sec[.Usec]"
 if unit is not specified, it returns unix-epoch time.
```

## convert unix epoch time to ISO-time string
example
```
tip> set vn=time(now)    ;# convert current local time to unix epoch time
tip> cat vn
vn : data(num) :  1762073282

tip> set vs=time(vn,str) ;# convert unix epoch time to ISO-time string
tip> cat vs
vs : data(str) :  2025-11-02 08:48:13.322786
```

## convert ISO-time string to unix epoch time
example
```
tip> set vs=time(now,str)  ;# convert current local time to ISO-time string
tip> cat vs
vs : data(str) :  2025-11-02 08:48:13.322786

tip> set vn=time(vs,utime) ;# convert ISO-time string to unix epoch time
tip> cat vn
vn : data(num) :  1762073282

tip> set vn=time(vs)   ;# argument utime can be omitted
tip> cat vn
vn : data(num) :  1762073282
```

## convert to year, month, day, hour, min, sec, us

|unit|type|value|
|:---:|:---:|:---:|
|str|ISO-time string|Y-M-D h:m:s.us|
|usec |floating point number|us   |
|sec  |floating point number|s + usec*0.001|
|min  |floating point number|m + sec/60|
|hour |floating point number|h + min/60|
|day  |floating point number|D + hour/24|
|month|floating point number|M + day/[28\|30\|31]|
|year |floating point number|Y + yday/[365\|366]|

> yday is the amount of days since the beginning of the year  
> the leap year is factored in

example
```
tip> set vn=time(now)
tip> set year=time(vn,year)
tip> set mon=time(vn,mon)
tip> set day=time(vn,day)
tip> set hour=time(vn,hour)
tip> set min=time(vn,min)
tip> set sec=time(vn,sec)
tip> set usec=time(vn,usec)

tip> cat year,mon,day,hour,min,sec,usec
year : data(num) :  2025.8366214
mon : data(num) :  11.045560696
day : data(num) :  2.3668208656
hour : data(num) :  8.8037007739
min : data(num) :  48.222046435
sec : data(num) :  13.322786093
usec : data(num) :  322786.09276

tip> set vs=time(vn,str)
tip> cat vs
vs : data(str) :  2025-11-02 08:48:13.322786
```

for more example, see
[ex17a](../ex/ex17a.md), [ex17b](../ex/ex17b.md), [ex18](../ex/ex18.md)

