# Command Reference

## (1) Usage to start up the tip interpreter from the shell

```
$ tip -h
usage: tip [options]

options:(where arg is option's argument)
 -h : show help message (also '--help')
 -v : show version (also '--version')
 -t arg: set window title (default is "tip")
 -g arg: set window geometry size (default is "800x600")
 -d arg: set drawing device (default is "xcairo")
 -e arg : execute a macro file
 --pdf arg : graph is drawn in pdf file (window is not open)
 --png arg : graph is drawn in png file (window is not open)
```

## (2) Syntax of the tip interpreter

### Multiple commands in a line

Separating by ";" you can put multiple command in a line
```
tip> title "x vs y1 and y2"; plot x y1; plot x y2 (rp:1) 
```

### Comment out the line

Put the "#" at the head of the line
```
tip> # comment out this line
```

Comment out from the middle of the line, put ";" before "#"
```
tip> plot x y ;# plotting data x and y  
```

### Variable

- **Data variable**

The data variable is array of number (or string) which is defined by
[set](ref/set.md) command.
```
tip> set n={1,2,3}
tip> set x=sin(n)
tip> ls x
x : data(num) : size=3
tip> cat x
x : data(num) :  0.84147098481 0.90929742683 0.14112000806
```
Explaining by C, the above example is doing like,
```
double n[]={1,2,3};
double x[sizeof(n)]; for(int i=0; i<sizeof(n); i++) x[i]=sin(n[i]);
```
- **Macro variable**

The macro variable is scalar of number (or string) which is defined by
[@](ref/var.md) command.  
Enclosing the macro variable in the brackets [ ]
it is replaced to the string which is formatted by it's value
```
tip> @ n=1
tip> @ x=sin([n])  ;# this is parsed as "@ x=sin(1)"
tip> ls *
n : number [1]
x : number [0.84147098481]
```
Actually, macro variable is replaced to the formatted string  before
parsing the command.  
so you can do like,
```
tip> @ n=1
tip> @ func=sin
tip> @ ret=x
tip> @ [ret]=[func]([n])  ;# this is parsed as "@ x=sin(1)"
tip> ls *
n : number [1]
x : number [0.84147098481]
func : string [sin]
ret : string [x]
```
- **Environment variable**

Environment variables defined in the shell are referenced by ${ }.

```
tip> prn ${SHELL}
/bin/bash
```

## (3) Commands of MacroTool
- [@](ref/var.md) : set macro variable
- [++,--](ref/incr.md) : increment(+1), decrement(-1) numerical macro variable
- [for,do,while,end](ref/loop.md) : for, do, while loop
- [if,elif,else,fi](ref/if_fi.md) : conditional branch
- [print](ref/print.md) : print arguments with macro variables format
- [fmt](ref/fmt.md) : set output format of macro variable
- [wait](ref/wait.md) : wait time or console input
- [sys](ref/sys.md) : execute system command
- [split](ref/split.md) : split string variable
- [calc](ref/calc.md) : evaluate the numerical expression
- [logic](ref/logic.md) : evaluate the logical expression
- q : quit the tip interpreter

## (4) Commands of drawing and handling data.
- [arc](ref/arc.md) : draw a circle in 2D-graph
- [box](ref/box.md) : draw the axis of 2D-graph in the box shape
- [box3](ref/box3.md) : draw the axes of 3D-graph
- [cat](ref/cat.md) : show data contents / concatenate data
- [cut](ref/cut.md) : set cut condition
- [div](ref/div.md) : divide the drawing area
- [elem](ref/elem.md) : copy data element to macro variable
- [exe](ref/exe.md) : execute macro file
- [fbox](ref/fbox.md) : draw a filled pattern box in 2D-graph
- [ffit](ref/ffit.md) : fit the frequency domain graph
- [fit](ref/fit.md) : fit the data in 2D-graph
- [fit3](ref/fit3.md) : fit the data in 3D-graph
- [fill](ref/fill.md) : draw a filled pattern object in 2D-graph
- [font](ref/font.md) : set text font
- [fplot](ref/fplot.md) : plot the frequency domain graph from the data
- [help](ref/help.md) : show help message
- [hfit](ref/hfit.md) : fit the histogram
- [hplot](ref/hplot.md) : plot the histogram from the data
- [hplot2](ref/hplot2.md): plot the 2D-histogram from the couple of data
- [line](ref/line.md) : draw a line in 2D-graph
- [ls](ref/ls.md) : list macro/data variables
- [mplot](ref/mplot.md) : plot mesh-graph(3D) or contour-graph(2D)
- [mread](ref/mread.md) : read the mesh data from the file
- [mset](ref/mset.md) : set mesh data
- [mwrite](ref/mwrite.md): write the mesh data to the file
- [opt](ref/opt.md) : set/show global options
- [plot](ref/plot.md) : plot the data in the 2D-graph
- [plot3](ref/plot3.md) : plot the data in the 3D-graph
- [read](ref/read.md) : read the data from the file
- [rm](ref/rm.md) : remove macro/data variables
- [set](ref/set.md) : set the data
- [sort](ref/sort.md) : sort the data in ascending order
- [stat](ref/stat.md) : calc statistics from the data
- [symb](ref/symb.md) : draw a symbol in 2D-graph
- [text](ref/text.md) : draw a text in 2D-graph
- [title](ref/title.md) : set the graph title
- [tfmt](ref/tfmt.md) : set the x-axis time format
- [vp](ref/vp.md) : set viewport of drawing area
- [write](ref/write.md) : write the data to the file
- [xerr](ref/xerr.md) : plot the x-error-bars in 2D-graph
- [xlab](ref/xlab.md) : set the x-axis label
- [yerr](ref/yerr.md) : plot the y-error-bars in 2D-graph
- [ylab](ref/ylab.md) : set the y-axis label
- [zlab](ref/zlab.md) : set the z-axis label in 3D-graph

## (5) Commands of EPICS CA (optional)

- [cainfo](ref/cainfo.md) : show information of record
- [caget](ref/caget.md) : get value of record
- [caput](ref/caput.md) : put value of record
- [camon](ref/camon.md) : open monitored record
- [cacheck](ref/cacheck.md): check if monitored record is updated
- [caclose](ref/caclose.md): close monitored record
