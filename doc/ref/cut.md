# cut
```
tip> cut
usage: cut v1,v2,... "expression"
 where v1,v2,... are data to cut
 new data v1_cut,v2_cut,... are created
example:
 cut x,y "0<x<1 & 1<y<2"
 plot x_cut y_cut
using option 'cc:' it is also done by
 plot x y (cc:"0<x<1 & 1<y<2")
```

Cut elements of the data listed in the argument by the specified condition  
It is created cut data named like v1_cut, v2_cut, ...

> list of data should be separated with commas and no spaces  
> condition of logical expression should be quoted by "" 

```
tip> cut a,b,c "a>0"    ; # OK
tip> cut a, b, c "a>0"  ; # NG spaces among data list
tip> cut a,b,c a>0      ; # NG condition is not quoted
```

> size of data should be same

```
tip> set x={1,2,3,4,5}
tip> set y={10,20,30}
tip> cut x,y "x>2"    ;# NG : size of y is different from size of x
size of y != size of x
```

example
```
tip> set name = {Taro, Jiro, Saburo, Shiro, Goro}
tip> set hight = {167, 183, 172, 175, 178}
tip> cat *
hight : data(num) :  167 183 172 175 178
name : data(str) :  Taro Jiro Saburo Shiro Goro

tip> cut name,hight "name={Taro,Goro}"
tip> cat *_cut
hight_cut : data(num) :  167 178
name_cut : data(str) :  Taro Goro

tip> cut name,hight "170<hight<180"
tip> cat *_cut
hight_cut : data(num) :  172 175 178
name_cut : data(str) :  Saburo Shiro Goro
```

see also
- [ex09: Data Cutting and simplified logical expression](../ex/ex09.md)
- [ex11: Plot 1D,2D Histograms and cutting the data](../ex/ex11.md)
