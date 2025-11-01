# mread
```
tip> mread
usage: mread x,y,z mesh-file [(opt)]
 read data and mesh-data
 where x is data of size N.
       y is data of size M.
       z is mesh-data of size N*M.
```

## option
### option with quotted argument by ""

- `fs:` field separater


## file format

data file is 3 column text separated by field separater.
The default field separater is a space character.

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

