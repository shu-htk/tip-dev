# write
```
tip> write
usage: write v1,v2,... file_name ([opt])
 where v1,v2,... is list of data to write
```

## option
### option with quotted argument by ""

- `fs:` field separater

## argument list of variable names

> argument list of variable names is separated by conmma with no spaces.

## wild-card matching to the variable name

| match to           | wild card |
|:---:|:---:|
|any string          |  *           |
|any character       |  ?           |
|one of the list of chars|[abc..], [a-z] |

> wild card is **not the regular expression**  

example
```
tip> do n 1 4; set v[n]=random(3,uni); end
tip> cat v*
v1 : data(num) :  0.72222002676 0.95971852632 0.6427698157
v2 : data(num) :  0.89879791527 0.059244560571 0.55197352802
v3 : data(num) :  0.78516065878 0.31009663609 0.25585515437
v4 : data(num) :  0.58039504503 0.26256283944 0.16205607036

tip> write v* test.dat

tip> sys cat test.dat
0.72222002676 0.89879791527 0.78516065878 0.58039504503
0.95971852632 0.059244560571 0.31009663609 0.26256283944
0.6427698157 0.55197352802 0.25585515437 0.16205607036

tip> read a test.dat

tip> cat a*
a1 : data(num) :  0.72222002676 0.95971852632 0.6427698157
a2 : data(num) :  0.89879791527 0.059244560571 0.55197352802
a3 : data(num) :  0.78516065878 0.31009663609 0.25585515437
a4 : data(num) :  0.58039504503 0.26256283944 0.16205607036
```
