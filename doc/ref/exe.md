# exe
```
tip> exe
usage: exe [macro_file] [arg1,arg2,...] [(opt)]
 execute macro_file
 arguments are referenced as macro variables
 they are named like x1=val,x2=val2,...
 if it is specified only values like val1,val2,...
 they are named $1=val1,$2=val2,...
 number of argumnts is named $#
```

## option

- `dm:`  set flag of debug-mode

## Execute macro file with arguments

> arguments are separated by commas with no spaces.

see also [args](args.md)

### (1) Named arguments

example macro file : `gaus.tip`
```
args title="test",ndata=1000,sigma=1,mean=0  ;# default parameters

title "[title]"
set x=random([ndata],gaus,[sigma],[mean])
hplot x (gd:1)
stat x (rc:1 cp:0.65,0.95)
```

executting `gaus.tip` with different parameters
```
tip> exe gaus.tip            ;# using default parameters
@ Statistics:
 entry=1000
 max= 3.36499
 min= -3.65553
 mean= 0.032266
 rms= 1.01432
 
tip> exe gaus.tip title="param set 1",ndata=100000,sigma=0.1,mean=5
@ Statistics:
 entry=100000
 max= 5.41261
 min= 4.57704
 mean= 4.9993
 rms= 0.0999921

tip> exe gaus.tip title="param set 2",ndata=200000,sigma=0.2,mean=3
@ Statistics:
 entry=200000
 max= 3.89212
 min= 2.0552
 mean= 3.00067
 rms= 0.200458
```

### (2) Unnamed arguments

|variable name|description|
|:---:|:---:|
| $# | number of arguments |
| $1 | 1st argument |
| $2 | 2nd argument |
| ... | ... |
| $N | Nth argument |

example macro file : `args.tip`
```
if [$#]
   do n 1 [$#]
      prn arg [n] is [$[n]]
   end
else   
   prn no args
fi
```

executting `args.tip` with different number of arguments

```
tip> exe args.tip
no args

tip> exe args.tip 1,2,3
arg 1 is 1
arg 2 is 2
arg 3 is 3

tip> exe args.tip 1,2,3,a,b,c
arg 1 is 1
arg 2 is 2
arg 3 is 3
arg 4 is a
arg 5 is b
arg 6 is c
```

## Execute macro file with debug-mode

example macro file : `test.tip`
```
@ s=abc
set x={1,2,3}
```
executing `test.tip`
```
tip> rm *
tip> exe test.tip
tip> ls *               ;# nothing to show

tip> exe test.tip (dm:1)   ;# with debug-mode option
tip> ls *               ;# variables defined in the macro file can be shown
$# : number [0]
s : string [abc]
x : data(num) : size=3

tip> cat x
x : data(num) :  1 2 3
```
