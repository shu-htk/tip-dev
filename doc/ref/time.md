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

## option
### option with quoted argument by ""

- `td:` set delimiters of ISO time format string 
>  argument of `td:` is 3 characters, "ABC"  
>  A is delimiter among year, month, day  
>  B is delimiter between day and hour  
>  C is delimiter among hour, min, sec

> default is "- :"

example
```
tip> set tn=time(now)
tip> set ts=time(tn,str)
tip> cat ts
ts : data(str) :  2025-11-05 12:26:53.353887

tip> set ts=time(tn,str) (td:"/_:")
tip> cat ts
ts : data(str) :  2025/11/05_12:26:53.353887
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
|str|ISO format time string|Y-M-D h:m:s.us|
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

## time() function for the macro variable

> time() function is also available to set macro variable.

example
```
tip> @ n=time(now)
tip> @ year=time(n,year)
tip> @ mon=time(n,mon)
tip> @ day=time(n,day)
tip> @ hour=time(n,hour)
tip> @ min=time(n,min)
tip> @ sec=time(n,sec)
tip> @ usec=time(n,usec)

tip> ls year,mon,day,hour,min,sec,usec
year : number [2025.8453539]
mon : number [11.151805759]
day : number [5.5541727768]
hour : number [13.300146649]
min : number [18.008799273]
sec : number [0.527976824]
usec : number [527999.609]

tip> @ s=time([n],str)
tip> ls s
s : string [2025-11-05 13:18:00.500000]
```

## omitting date/time in the ISO time format

> omitting time, it is complemented with current time  
> omitting date, it is complemented with current date  

example
```
tip> @ t1=time("2020-02-03")  ;# omitting time, convert to unix epoch time
tip> @ t2=time("13:26:49")    ;# omitting date, convert to unix epoch time
tip>
tip> @ ts1=time([t1],str)     ;# convert t1 to ISO format time string
tip> @ ts2=time([t2],str)     ;# convert t2 to ISO format time string
tip>
tip> ls ts?
ts1 : string [2020-02-05 15:12:09.500000]  ;# time is complemented with the current time
ts2 : string [2025-11-05 13:26:49.599999]  ;# date is complemented with the current date
```

## making the time array

example
```
tip> @ t1 = time("1999-12-31 00:00:00.0") ;# convert to unix epoch time
tip> @ t2 = time("2000-01-02 00:00:00.0") ;# convert to unix epoch time
tip> set t = range(13,[t1],[t2])          ;# make array of unix epoch time
tip> set ts = time(t,str)                 ;# convert to ISO time string
tip> cat ts (fs:"\n")
ts : data(str) :
1999-12-31 00:00:00.000000
1999-12-31 04:00:00.000000
1999-12-31 08:00:00.000000
1999-12-31 12:00:00.000000
1999-12-31 16:00:00.000000
1999-12-31 20:00:00.000000
2000-01-01 00:00:00.000000
2000-01-01 04:00:00.000000
2000-01-01 08:00:00.000000
2000-01-01 12:00:00.000000
2000-01-01 16:00:00.000000
2000-01-01 20:00:00.000000
2000-01-02 00:00:00.000000
```

for more example, see
[ex17a](../ex/ex17a.md), [ex17b](../ex/ex17b.md), [ex18](../ex/ex18.md)
