# set
```
tip> set
usage: set v = {x0,x1,x2,...}
       set v = range(N,x0,x1)
       set v = incr(N,x0,dx)
       set v = random(N,uni|gaus|exp[,params...]) [(opt)]
       set v = time(t[,unit]) 
       set v = expression
 set the data v by some expressions.
 see 'range', 'random', 'time' for more information.
```

## set data using initializer list {}

> initializer list is enclosed by { } separated by comma or space.

```
tip> set x = {1, 2, 3} # OK: you can put spaces between value and comma
tip> set x={1,2,3}     # OK
```

## set data using range()

set data by initial value(x0) and final value(x1)

> [range](range.md)() is a function exclusive to the `set` command
> and cannot be used in the expressions.


example
```
tip> set x = range(10, 1, 10)  ;# OK: you can put spaces between value and comma
tip> set x = range (10, 1, 10) ;# NG: you can not put spaces between range and (
tip> set x=range(10,1,10)      ;# OK
tip> set x = y + range(10,1,10) ;# NG: you can not use it in the expression
```

## set data using incr()

set data by initial value(x0) and incremental value(dx)

```
tip> incr
usage: set v = incr(N,x0,dx)
  set N-size data starting from x0 increment by dx.
  ex.) incr(5,0,2) set the data {0, 2, 4, 6, 8}.
  
tip> set x=incr(5,0,2)
tip> cat x
x : data(num) :  0 2 4 6 8
```

## set data using random()

> [random](random.md)() is a function exclusive to the `set` command
> and cannot be used in the expressions.

example
```
tip> set x=random(1000,uni,-10,10) ;# uniform dist. -10 <= x <= 10
tip> set x=random(1000)            ;# default 0 <= x <= 1

tip> set x=random(1000,gaus,0.5,1) ;# Gaussian dist. sgm=0.5, mean=1 
tip> set x=random(1000,gaus)       ;# default sgm=1, mean=0 

tip> set x=random(1000,exp,2)      ;# exponential dist. tau=2
tip> set x=random(1000,exp)        ;# default tau=1

tip> set x=random(10,gaus)+random(10,exp); NG: you can not use it in the expression
tip> # for the above case you should do like,
tip> set x1=random(10,gaus)
tip> set x2=random(10,exp)
tip> set x=x1+x2
```

## set data using time()

> [time](time.md)() is a function exclusive to the [set](set.md) and
> [@](var.md) command
> and cannot be used in the expressions.

## set data by expression

> If there are variables in the expression, new data is created which size
> is the same as data in the expression.

> If there are no variables in the expression, size of new data is 1.

example
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

tip> set x = exp(1)  ;# no variables in the expression
tip> ls x
x : data(num) : size=1  ;# data size is 1
tip> cat x
x : data(num) :  2.7182818285
tip>
```
