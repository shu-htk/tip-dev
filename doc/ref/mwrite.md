# mwrite
```
tip> mwrite
usage: mwrite x,y,z mesh-file [(opt)]
 write data and mesh-data
 where x is data of size N.
       y is data of size M.
       z is mesh-data of size N*M.
```

## option
### option with quoted argument by ""

- `fs:` field separator


## file format

data file is 3 column text separated by field separator.
The default field separator is a space character.

|x|y|z| comment|
|---|---|---|---|
|x1|y1|z11| |
|x2|y1|z21| |
|...|...|...| |
|xN|y1|zN1| |
| | | | here is a space line|
|x1|y2|z12| |
|x2|y2|z22| |
|...|...|...| |
|xN|y2|zN2| |
| | | | here is a space line|
|...|...|...| |
|x1|yM|z1M| |
|x2|yM|z2M| |
|...|...|...| |
|xN|yM|zNM| |


## reading mesh file by gnuplot

The data file written by `mwrite` can be plotted by gnuplot
using `splot`.

example
```
$ tip
tip> set x = range(32,-3.2,3.2)
tip> set y = range(30,-3,3)
tip> mset z = log(1+2*x*x+3*y*y)
tip> mwrite x,y,z mesh.dat
tip> q

$ gnuplot
gnuplot> splot 'mesh.dat' w l
```
