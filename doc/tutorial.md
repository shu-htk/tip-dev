# Tutorial

## Starting the tip interpreter

from the Linux shell,
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
![](fig/tut01.png)

"[title](ref/title.md)" specify the text at the top of the graph.  
"[set](ref/set.md)" create the data instance,
where data is an array of numbers.  
"[plot](ref/plot.md)" draw the 2D-plot using data x and y.  
"[fit](ref/fit.md)" make the fitting curve by the specified function,
in this example "quad" means Quadratic function. 

The arguments enclosed in ( ) are options.

`(lw:0)` set the line width 0, i.e. not draw the line.  
`(st:star)` set the [symbol](#symbols) style 'star shape'.  
`(sc:red)` set the symbol [color](#colors) red.  
`(gd:1)` set the flag to draw the grid lines in the graph.  
`(cp:1,200)` set the comment position about the fitting parameters
at (x=1, y=200) in the graph coordinate.  
`(lc:blue) `set the line [color](#colors) blue. 

The options which are put at the back of the command are
the local options. (i.e. they only applied to the same line).  
On the other hand the options defined by [opt](ref/opt.md) command
is the global options.
```
tip> opt (lw:0 st:star sc:red gd:1)
```
The global options are applied to all bellow this command.

## Showing data information

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
In this  example, `test.csv` is a CSV text file that has 3 columns of data.  
"[read](ref/read.md)" is reading the data from the file, at that time,
the column number is automatically added to the specified variable name
like v1, v2, v3.  
This feature is convenient if there are many columns in the data file.  

"[xlab](ref/xlab.md)"/"[ylab](ref/ylab.md)" specify x-axis/y-axis label
respectively.

`(fs:",")` is option to specify the filed separator of data.  
`(lc:red)` and `(lc:blue)` are options to specify the line color.   
`(rp:1)` is option to do 'replot' i.e. over-drawing in the existing graph. 

![](fig/tut02b.png)

If the number of columns in the file is not so large, you can specify
variable name for each column like,
```
tip> read x,y,z test.csv (fs:",")
```
where data of 1st, 2nd, 3rd columns are named x, y, z respectively.

In some cases, 1st column is assigned for x-axis and the rests are
assigned for y-axis,  
in that case you can do like,
```
tip> read x,y test.csv (fs:",")
```
where 1st column is named x and 2nd, 3rd are named to y1, y2 respectively.

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
![](fig/tut02c.png)

"[fbox](ref/fbox.md)" draws the fill-area-box,
"[line](ref/line.md)" draws a line,
"[text](ref/text.md)" draws text in the graph.  
`(ft:solid)` set the [fill-area-style](#fill-area-style) "solid".  
`(rc:1)` set the flag of relative axis coordinate.  
where relative axis coordinate means that the axis-range is defined
from 0.0 to 1.0 for both of x-axis and y-axis.

## Histogram 1D

```
tip> title "Histogram of Gaussian distribution (sigm=5,mean=10)"
tip> ylab "Num of entries"
tip> set x = random(100000,gaus,5,10)
tip> hplot x (nb:50)
tip> hfit x gaus (lc:green cp:0.03,0.9 rc:1 ts:0.8)
tip> stat x (cp:0.03,0.6 rc:1 ts:0.8)
```
![](fig/tut03.png)

"[random](ref/random.md)" make random distribution with specified data size.  
In this example,
it is generated 100000 sizes of Gaussian distribution with sigma=5 mean=10.  
"[hplot](ref/hplot.md)" creates a 1D-histogram of the specified data.
In this example, a histogram with bin number 50 is generated.  
The x-range of the histogram is calculated to include all data
unless it is specified the option `(xr:Xmin,Xmax)`.  
"[hfit](ref/hfit.md)" makes a fitting curve to the histogram
with the specified function and it is drawn over the existing plot.
`(cp:0.03,0.9 rc:1)` specify to draw the fitting information at x=0.05,y=0.9
in the relative coordinate.  
`(ts:0.8)` specify the text size 0.8 (default is 1.0).  
"[stat](ref/stat.md)" make the statistics information of the specified data,
and it is drawn over the existing plot if the option `(cp:)` is specified.

## Histogram 2D

```
tip> title "2D-Histogram of gaus.dist (sigm=5,mean=10 and sigm=8,mean=20)"
tip> zlab "Num of entries"
tip> set x = random(100000,gaus,5,10)
tip> set y = random(100000,gaus,8,20)
tip> hplot2 x y (nx:30 ny:30)
```
![](fig/tut04.png)

"[hplot2](ref/hplot2.md)" makes 2D-histogram of a pair of data.  
`(nx:30)` and `(ny:30)` are options to specify x-axis and y-axis
bin number relatively.

## Quit the tip interpreter

```
tip> q
```
It is saved the command history to the file `.tip_history` in your
working directory.

## Making a macro file and executing it

Copy the command history to the macro file like,

```
$ cp .tip_history some_macro.tip
```

and edit the file `some_macro.tip`

then do,

```
tip> exe some_macro.tip
```

## Colors

To find color names defined in tip, type `opt color` or `opt c`.
```
tip> opt color
color names of the symbol/line/fill :
 red(1), yellow(ylw,2), green(grn,3), aqua(aqu,4), pink(pnk,5)
 wheat(wht,6), gray(gry,7), brown(brn,8), blue(blu,9), violet(vio,10)
 cyan(cyn,11), turquoise(tqs,12), magenta(mgt,13), salmon(smn,14)
 black(blk,15), white(whi,0)
```

## Symbols

To find symbols names defined in tip, type `opt symbol` or `opt s`.
```
tip> opt symbol
names of the symbol :
 non(0), dot(1), plus(pls,2), star(str,3), arc(4), cross(crs,5), square(sqr,6),
 triangle(tri,7), arccross(acc,8), arcdot(acd,9), square2(sq2,10),
 diamond(dia,11), star2(st2,12), square3(sq3,13), cross2(cr2,14), star3(st3,15),
 blacksqr,(bsq,16)
```

## Fill-Area-Style

To find fill-area names defined in tip, type `opt fill` or `opt f`.
```
tip> opt fill
names of the fill area style:
 null(-1), solid(s,0), hor(1), ver(2), p45(3), n45(4), p30(5), n30(6), hv(7), pn45(8)
```
