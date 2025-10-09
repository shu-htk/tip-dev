# Command Reference

## (1) usage to start tip from the shell

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

## (2) syntacs of the tip interpriter

### multiple commands in a line

separating by ";" you can put multiple command in a line
```
tip> plot x y1; plot x y2 (rp:1)
```

### comment out the line

put the "#" at the head of the line
```
tip> # comment out this line
```

to comment out from the middle of the line, put ";" before "#"
```
tip> plot x y ;# plotting data x and y  
```

### macro variable

if there is macro variable in the brackets "[" and "]" it is  
replaced to the value before parsing the command line  
```
tip> @ n=1
tip> @ func = sin
tip> @ x[n] = [func]([n])  ;# this is parsed as @ x1 = sin(1)
tip> ls *
n : number [1]
x1 : number [0.84147098481]
func : string [sin]
```
see also [command @](ref/var.md).

### commands of MacroTool
- [@](ref/var.md) : define numerical or string variable
- [++,--](ref/incr.md) : increment(+1), decrement(-1) numerical variable
- [for,do,while,end](ref/loop.md) : for, do, while loop
- [if,elif,else,fi](ref/if_fi.md) : conditional branch
- [print](ref/print.md) : print arguments with macro variables formated
- [fmt](ref/fmt.md) : set output format of macro variable
- [wait](ref/wait.md) : wait time or console input
- [sys](ref/sys.md) : execute system command
- [calc](ref/calc.md) : evaluate the numerical expression
- [logic](ref/logic.md) : evaluate the logic expression
- q : quit the tip interpriter

### commands of tip
- [arc](ref/arc.md) : draw a circle in 2D-graph
- [box](ref/box.md) : draw the axis of 2D-graph in the box shape
- [box3](ref/box3.md) : draw the axes of 3D-graph
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
- [mplot](ref/mplot.md) : plot mesh-graph(3D) or contour-graph(2D)
- [mread](ref/mread.md) : read the mesh data from the file
- [mset](ref/mset.md) : set mesh data
- [mwrite](ref/mwrite.md): write the mesh data to the file
- [opt](ref/opt.md) : set/show global options
- [plot](ref/plot.md) : plot the data in the 2D-graph
- [plot3](ref/plot3.md) : plot the data in the 3D-graph
- [read](ref/read.md) : read the data from the file
- [set](ref/set.md) : set the data
- [sort](ref/sort.md) : sort the data in ascending order
- [sqar](ref/sqar.md) : draw a square in 2D-graph
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
