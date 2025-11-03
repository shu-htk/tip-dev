# set
```
tip> set
usage: set v = {x0,x1,x2,...}
       set v = range(N,x0,x1)
       set v = random(N,uni|gaus|exp[,params...]) [(opt)]
       set v = time(t[,unit]) 
       set v = expression
 set the data v by some expressions.
 see 'range', 'random', 'time' for more information.
```

## set data using initializer list {}

> initializer list is enclosed by {}, separated by comma or space.

```
tip> set x = {1, 2, 3} # OK: you can put spaces between value and comma
tip> set x = {1,2,3}   # OK
tip> set x={1,2,3}     # OK
```

## set data using range()

see [range](range.md)
```
tip> set x = range(10,1,10)    ;# OK
tip> set x = range(10, 1, 10)  ;# OK: you can put spaces between value and comma
tip> set x = range (10, 1, 10) ;# NG: you can not put spaces between range and (
tip> set x=range(10,1,10)      ;# OK
```

## set data using random()

see [random](random.md)

> spacing rule is same as range()


## set data using time()

see [time](time.md)

> spacing rule is same as range()


## set data by experssion

> set y = expression(x1,x2,...,xn)  
> where size of data x1,x2,...,xn in the expression should be the same

```
tip> rm *
tip> set a={1,2,3}
tip> set b={4,5,6}
tip> set c=a+b      ;# data c is created as the same size of data a and b
tip> cat *
a : data(num) :  1 2 3
b : data(num) :  4 5 6
c : data(num) :  5 7 9

tip> set d={7,8}    ;# size of data d is different from data a and b
tip> set e=a+b+d    ;# NG: data e is not created 
size of a != size of d
tip> cat *
a : data(num) :  1 2 3
b : data(num) :  4 5 6
c : data(num) :  5 7 9
d : data(num) :  7 8
```
