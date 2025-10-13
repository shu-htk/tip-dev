# ex17a: Plot ISO-time-format data with time-axis format
```
opt (gd:1)
div 1 3

@ n = 5000 ;# number of data
@ ts1 = "2020-01-01 00:00:00" ;# string of the start time (local time)
@ ts2 = "2024-12-31 23:59:59" ;# string of the end time (local time)
@ t1 = time([ts1])            ;# convert ts1 to the unix epoch time (UTC)
@ t2 = time([ts2])            ;# convert ts2 to the unix epoch time (UTC)

opt (sd:0)                    ;# set random seed 0 (fixed to compare ex17b)
set t = range([n],[t1],[t2])  ;# ranged data of the unix time from t1 to t2
set v = random([n],exp)       ;# dummy data (random exponetial) for y-axis

title "[ts1] - [ts2] (x-axis is time format)"
plot t v (tf:"%Y-%m-%d" xn:6) ;# x-axis is "year-month-day"

set ts = time(t,str)         ;# convert the unix time to string (local time)
title "cut by 'ts==2022-*-*' (x-axis is time format)"
plot t v (cc:"ts==2022-*-*" tf:"%Y-%m-%d") ;# choose 2022 by the time string

cut t,v "ts==2022-04-*"     ;# choose 2022-4 by the time string
@ day_sec = 24*3600
title "cut by 'ts==2022-04-*' (x-axis is time format)"
plot t_cut v_cut (tf:"%d" xt:[day_sec]  xn:1 st:star)

```
![](../fig/ex17a.png)
