# Tutorial

## Starting the tip interpriter

from the linux shell,
```
$ tip
```
where you should set the shell's command path to the executable file of tip 

see [how to install](install.md) to learn making executable file.

## Making data and plot

```
tip> title "Plotting the data and fitting the curve"
tip> set x = {1,2,3,4,5,6,7,8,9,10}
tip> set y = 2*x*x
tip> plot x y (lw:0 st:star sc:red gd:1)
tip> fit x y quad (cp:1,200 lc:blue)
```
![macro/tut01.tip](fig/tut01.png)

`title` specify the text at top of the graph.  
`set` make instance of the data, where data is array of number.  
`plot x y` plot the data x and y.  
`fit x y quad` make the fitting by Quadratic function. 

arguments between the bracket '(' and ')' are options.  

`(lw:0)` set the line width 0, i.e. not draw the line.  
`(st:star)` set the symbol's style 'star shape'. [see symbols](#symbols)  
`(sc:red)` set the symbol's color red. [see colors](#colors)  
`(gd:1)` set the flag to draw the grid lines in the graph.  
`(cp:1,200)` set comment position about the fitting parameters.  
`(lc:blue) `set the line's color blue. 

options which are put at the back of the command are
local options. (i.e. they only applied to the same line)  
on the other hand [opt](ref/opt.md) command set global options.
```
tip> opt (lw:0 st:star sc:red gd:1)
```
these options are applied to all bellow this command.

data made by user are listed by [ls](ref/ls.md) command.
```
tip> ls *
x : data(num) : size=10
y : data(num) : size=10
```

contents of the data is shown by [cat](ref/cat.md) command.
```
tip> cat y
y : data(num) :  2 8 18 32 50 72 98 128 162 200
```

## Reading data from the file and plot

```
tip> title "Reading test.csv"
tip> read v test.csv (fs:",")
tip> xlab "1st column data" 
tip> ylab "2nd and 3rd column data" 
tip> plot v1 v2 (lc:red)
tip> plot v1 v3 (lc:blue rp:1)
```
where `test.csv` is 3 columns CSV text data.
the column number is automatically added to tha data name v  
like v1, v2, v3.  
`xlab` specify x-axis label and `ylab` specify y-axis label.

`(fs:",")` is option to specify the filed separater of data.  
`(lc:red)` and `(lc:blue)` are options to specify the line's color.   
`(rp:1)` is option to do 'replot' i.e. over-drawing in the exsisting graph. 

![macro/tut02b.tip](fig/tut02b.png)

another method to define the data name is like,
```
tip> read x,y,z test.csv (fs:",")
```
where 1st column is x, 2nd is y, 3rd is z.

also you can do like,
```
tip> read x,y test.csv (fs:",")
```
where 1st column is x and 2nd and 3rd are named to y1 and y2.

in general,

```
 read v1,v2,...,vN  file_of_Mth_column.dat
```

- if N < M, last (M-N+1) columns are named as vN1, vN2, ..., vNx (x=M-N+1)
- if N > M, vM+1,...,VN are ignored

## Drawing fill box, line and text

```
tip> title "Drawing fill box, line and text"
tip> read x,y test.csv (fs:",")
tip> xlab "x" ; ylab "y1, y2" 
tip> plot x y1 (lc:red)
tip> plot x y2 (lc:blue rp:1)
tip> opt (rc:1)
tip> fbox 0.80 0.95 0.80 0.95 (ft:solid)
tip> line 0.82 0.86 0.90 0.90 (lc:red);  text 0.88 0.90 "y1"
tip> line 0.82 0.86 0.85 0.85 (lc:blue); text 0.88 0.85 "y2"
```
![macro/tut02c.tip](fig/tut02c.png)

separating by ";", you can put multiple commands in the same line
like `xlab "x"; ylab "y1, y2"`  
`fbox` is command to draw the fill-area-box in the graph.
[see fill-area-style](#fill-area-style).  
`line` is command to draw the line.  
`text` is command to draw the text.  
`(ft:solid)` set the fill-area-style "solid".  
`(rc:1)` is option to set the flag of relative axis coordinate.  
where relative axis coordinate means that the axis-range is defined
from 0.0 to 1.0 for both of x-axis and y-axis.

## Histogram 1D

```
tip> title "Histogram of gaussian distribution (sigm=5,mean=10)"
tip> ylab "Num of entries"
tip> set x = random(100000,gaus,5,10)
tip> hplot x (nb:50)
tip> hfit x gaus (lc:green cp:0.03,0.9 rc:1 ts:0.8)
tip> stat x (cp:0.03,0.6 rc:1 ts:0.8)
```
![macro/tut03.tip](fig/tut03.png)

`set x = random(100000,gaus,5,10)` make data of random gaussian distribution
with sigma=5 mean=10.
[see random](#ref/random.md)  
`hplot x (nb:50)` makes histogram of data x 
where bin number 50, x-range is set to include all data of x.  
you can change the x-range by the option `(xr:Xmin,Xmax)`.

`hfit x gaus` make fitting of gaussian curve to the histogoram.  
the fitting curve is drawn with green line, fitting information is
drawn at the position x=0.05,y=0.9 in relative coordinate.  
`(ts:0.8)` specify text size 0.8 (default is 1.0).

`stat x (cp:0.05,0.9 rc:1)` put the statistics information of data
at the position x=0.03,y=0.9 in relative coordinate.

## Histogram 2D

```
tip> title "2D-Histogram of gaus.dist (sigm=5,mean=10 and sigm=8,mean=20)"
tip> zlab "Num of entries"
tip> set x = random(100000,gaus,5,10)
tip> set y = random(100000,gaus,8,20)
tip> hplot2 x y (nx:30 ny:30)
```
![macro/tut04.tip](fig/tut04.png)

`hplot2 x y (nx:30 ny:30)` makes 2D-histogram of data x and y.  
`(nx:30)` and `(ny:30)` are options to specify x-axis and y-axis
bin number relatively.

## Quit the tip interpriter

```
tip> q
```
the command history is saved to the file `.tip_history` in your
working directory.

## Making macro file and execute it

you can copy the command history to the macro file like,

```
$ cp .tip_history some_macro.tip
```

and edit the file `some_macro.tip`

then do,

```
tip> exe some_macro.tip
```

## Colors

```
tip> opt color
color names of the symbol/line/fill :
 red(1), yellow(ylw,2), green(grn,3), aqua(aqu,4), pink(pnk,5)
 wheat(wht,6), gray(gry,7), brown(brn,8), blue(blu,9), violet(vio,10)
 cyan(cyn,11), turquoise(tqs,12), magenta(mgt,13), salmon(smn,14)
 black(blk,15)
```

## Symbols

```
tip> opt symbol
names of the symbol :
 non(0), dot(1), plus(pls,2), star(str,3), arc(4), cross(crs,5), square(sqr,6),
 triangle(tri,7), arccross(acc,8), arcdot(acd,9), square2(sq2,10),
 diamond(dia,11), star2(st2,12), square3(sq3,13), cross2(cr2,14), star3(st3,15),
 blacksqr,(bsq,16)
```

## Fill-Area-Style

```
tip> opt fill
names of the fill area style:
 null(-1), solid(s,0), hor(1), ver(2), p45(3), n45(4), p30(5), n30(6), hv(7), pn45(8)
```

## Help

to leran what commands are available in the tip intepriter.

```
tip> help
list of commands:
 arc   : draw a circle in 2D-graph
 box   : draw the axis of 2D-graph in the box shape
 box3  : draw the axes of 3D-graph
 cat   : show data contents / concatenate data
 cut   : set cut condition
 div   : divide the drawing area
 elem  : copy data element to macro variable
 exe   : execute macro file
 fbox  : draw a filled pattern box in 2D-graph
 ffit  : fit the frequency domain graph
 fit   : fit the data in 2D-graph
 fit3  : fit the data in 3D-graph
 fill  : draw a filled pattern object in 2D-graph
 font  : set text font
 fplot : plot the frequency domain graph from the data
 help  : show help message
 hfit  : fit the histogram
 hplot : plot the histogram from the data
 hplot2: plot the 2D-histogram from the couple of data
 line  : draw a line in 2D-graph
 ls    : list macro/data variables
 mplot : plot mesh-graph(3D) or contour-graph(2D)
 mread : read the mesh data from the file
 mset  : set mesh data
 mwrite: write the mesh data to the file
 opt   : set/show global options
 plot  : plot the data in the 2D-graph
 plot3 : plot the data in the 3D-graph
 read  : read the data from the file
 rm    : remove macro/data variables
 set   : set the data
 sort  : sort the data in ascending order
 sqar  : draw a square in 2D-graph
 stat  : calc statistics from the data
 symb  : draw a symbol in 2D-graph
 text  : draw a text in 2D-graph
 title : set the graph title
 tfmt  : set the x-axis time format
 viewport : set drawing area in the window (abbr. vp)
 write : write the data to the file
 xerr  : plot the x-error-bars in 2D-graph
 xlab  : set the x-axis label
 yerr  : plot the y-error-bars in 2D-graph
 ylab  : set the y-axis label
 zlab  : set the z-axis label in 3D-graph
macro commands:
 @     : define numerical or string variable
 ++    : increment(+1) numerical variable
 --    : decrement(-1) numerical variable
 for   : foreach loop
 do    : numerical ranged loop
 break : break for/do/while loop
 continue : continue for/do/while loop
 end   : end of for/do/while loop
 if    : conditional branch
 elif  : else if
 else  : else
 fi    : end of if
 print : print arguments (abbr. pr)
 println: print arguments and '\n' (abbr. prn)
 fmt   : set output format of macro variable
 wait  : wait time or console input
 sys   : execute system command
 calc  : evaluate the numerical expression
 logic : evaluate the logic expression
 q     : terminate this program

 without arguments, you get usage of the above commands
```


