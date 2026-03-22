# mread
```
tip> mread
Usage: mread x,y,z mesh_file [(opt)]
Read data and mesh data.
  x : size N
  y : size M
  z : size N×M
```

## option
### option with quoted argument

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

