# チュートリアル

## tipインタープリターの起動

Linux等で端末を開き、シェルから以下のように起動します。

```
$ tip
```

シェルのコマンドパスにtipの実行ファイルのパスをセットする必要があります。

実行ファイルの作成方法は、 [how to install](install.md) 
を見て下さい。


## データ作成とプロット

```
tip> title "Plotting the data and fitting the curve"
tip> set x = {1,2,3,4,5,6,7,8,9,10}
tip> set y = 2*x*x
tip> plot x y (lw:0 st:star sc:red gd:1)
tip> fit x y quad (cp:1,200 lc:blue)
```
![](../doc/fig/tut01.png)

"[title](ref/title.md)" はグラフ上部のタイトルテキストを指定します。  
"[set](ref/set.md)" はデータのインスタンスを生成します。ここでデータとは数の配列です。  
"[plot](ref/plot.md)" はデータxとyの2次元のグラフを描きます。    
"[fit](ref/fit.md)" は指定された関数でフィッティングカーブを描きます。
この例では二次関数(Quadratic function)"quad"を用いています。  

( ) で囲まれた引数はコマンドオプションです。  

`(lw:0)` はグラフの線の幅を0にします、つまり線を描きません。    
`(st:star)` は シンボル（[symbol](#symbols)）のスタイルを
'star'（アスタリスク）にします。  
`(sc:red)` はシンボルの色（ [color](#colors)）を赤にします。    
`(gd:1)` はグラフの中にグリッドの点線を描くフラグをセットします。    
`(cp:1,200)` はコメントの位置をしていします。ここではフィッティングで得られた係数を
グラフの座標で(x=1, y=200)の位置に描きます。    
`(lc:blue)` はグラフの線の色（ [color](#colors)）を青にします。   

上の例のようにコマンド行の後ろに指定されたオプションはローカルオプション
（その行のコマンドにのみ適用される）です。
一方、 以下のように、[opt](ref/opt.md) コマンドで指定されたオプションは
グローバルオプションになります。

```
tip> opt (lw:0 st:star sc:red gd:1)
```

グローバルオプションは、この行以後のすべてのコマンドに適用されます。


## データ情報の表示

ユーザーが作成したデータの情報は [ls](ref/ls.md) コマンドで見ることができます。

```
tip> ls *
x : data(num) : size=10
y : data(num) : size=10
```

データの中身は [cat](ref/cat.md)コマンドで見れます。
 
```
tip> cat y
y : data(num) :  2 8 18 32 50 72 98 128 162 200
```

## ファイルからのデータ読み出しとプロット

```
tip> title "Reading test.csv"
tip> read v test.csv (fs:",")
tip> xlab "1st column data" 
tip> ylab "2nd and 3rd column data" 
tip> plot v1 v2 (lc:red)
tip> plot v1 v3 (lc:blue rp:1)
```

この例では、`test.csv` は3列のデータからなるCSVのテキストファイルです。  

"[read](ref/read.md)" はファイルの中身を指定した変数に読み込みます。
変数名には列の番号が v1,v2,v3のように自動的に付加されます。
列の数が多いデータファイルの読むときに便利です。  
"[xlab](ref/xlab.md)"/"[ylab](ref/ylab.md)" はそれぞれ x座標、y座標のラベルを指定します。  
`(fs:",")` はフィールドセパレーターを指定するオプションで、ここではCSVファイルを列で分離するために`","`を指定しています。  
`(lc:red)`と`(lc:blue)` は線の色を指定しています。     
`(rp:1)`は'replot'オプションです。つまり既にあるグラフの上に上書きします。


![](../doc/fig/tut02b.png)

読み込むファイルの列数がそれほど多くないときは、
以下のように変数名をそれぞれの列で指定できます。

```
tip> read x,y,z test.csv (fs:",")
```

ここでは、1列目、2列目、3列目のデータがそれぞれ、変数 x, y, z に読み込まれています。


場合によっては、1列目のデータをx座標に、2列目以後のデータをy座標にしたいときが
あります。そのような場合、以下のようにすることができます。

```
tip> read x,y test.csv (fs:",")
```

ここでは、xは１列目のデータ、yには2列目を起点とした列番号が付与されそれぞれy1,y2となります。


## フィルボックス, 線 テキストの描画

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
![](../doc/fig/tut02c.png)

`fbox`,`line`,`text`などのコマンドは`plot`などで描画されたグラフのエリア内に図形や文字を描画します。

"[fbox](ref/fbox.md)" はフィルボックスを描きます。  
"[line](ref/line.md)" は線を描きます。  
"[text](ref/text.md)" はテキストを描きます。

`(ft:solid)` のオプション指定で塗りつぶしスタイル（ [fill-area-style](#fill-area-style)）が "solid"になります。オプションが指定されないとデフォルトで塗りつぶしなしで枠のみ描画されます。

`(rc:1)` のオプションは図形や文字の描画位置を相対座標に設定します。
ここで相対座標とは、x軸、y軸の範囲が0.0から1.0と定義された座標系です。


## 1次元ヒストグラム

```
tip> title "Histogram of Gaussian distribution (sigm=5,mean=10)"
tip> ylab "Num of entries"
tip> set x = random(100000,gaus,5,10)
tip> hplot x (nb:50)
tip> hfit x gaus (lc:green cp:0.03,0.9 rc:1 ts:0.8)
tip> stat x (cp:0.03,0.6 rc:1 ts:0.8)
```
![](../doc/fig/tut03.png)

"[random](ref/random.md)" は`set`コマンドで使える関数で、指定されたサイズ、関数分布で乱数データを生成します。  
この例では
100000のサイズの正規分布（Gaussian distribution,sigma=5 mean=10）が生成されます。    
"[hplot](ref/hplot.md)"は データから1次元のヒストグラムを生成しプロットします。
`(nb:50)` オプションでヒストグラムのビン数を50に設定しています。   
`(xr:Xmin,Xmax)`オプションを設定するとヒストグラムの横軸の範囲を指定できます。
デフォルトでは、横軸の範囲はデータが全て収まるように自動的に設定されます。  
"[hfit](ref/hfit.md)"は指定された関数でヒストグラムをフィッティングして
曲線を求めヒストグラムの上に描画します。  
`(cp:0.03,0.9 rc:1)` オプションはフィッティングで得られた係数の情報を指定された
座標の位置に描きます。  
ここでは相対座標でx=0.05,y=0.9の位置に描いています。   
`(ts:0.8)`オプションはテキストのサイズを指定します（デフォルト値は1.0）。  
"[stat](ref/stat.md)"はデータの統計情報を指定の位置に描きます。

## 2次元ヒストグラム

```
tip> title "2D-Histogram of gaus.dist (sigm=5,mean=10 and sigm=8,mean=20)"
tip> zlab "Num of entries"
tip> set x = random(100000,gaus,5,10)
tip> set y = random(100000,gaus,8,20)
tip> hplot2 x y (nx:30 ny:30)
```
![](../doc/fig/tut04.png)

"[hplot2](ref/hplot2.md)" は指定された2つのデータから2次元ヒストグラムを生成しプロットします。  
`(nx:30)` と `(ny:30)`のオプションは、それぞれ2次元ヒストグラムのx軸、y軸のビン数を設定します。

## tipインタープリターを終了する

```
tip> q
```

終了すると、コマンドヒストリーファイル `.tip_history`がカレントディレクトリに
保存されます。


## マクロファイルの作成と実行


コマンドヒストリーのファイルをマクロファイルとしてコピーします。


```
$ cp .tip_history some_macro.tip
```

コピーしたマクロファイル`some_macro.tip`を編集します。

その後、`tip`を起動して以下のようにしてマクロファイルを実行します。

```
tip> exe some_macro.tip
```


## Colors

tipインタプリタで定義されている色の名前は`opt color`または略して`opt c`と
打つことで知ることができます。  
```
tip> opt color
color names of the symbol/line/fill :
 red(1), yellow(ylw,2), green(grn,3), aqua(aqu,4), pink(pnk,5)
 wheat(wht,6), gray(gry,7), brown(brn,8), blue(blu,9), violet(vio,10)
 cyan(cyn,11), turquoise(tqs,12), magenta(mgt,13), salmon(smn,14)
 black(blk,15)
```

## Symbols

tipインタプリタで定義されているシンボルの名前は`opt symbol`または略して`opt s`と
打つことで知ることができます。  
```
tip> opt symbol
names of the symbol :
 non(0), dot(1), plus(pls,2), star(str,3), arc(4), cross(crs,5), square(sqr,6),
 triangle(tri,7), arccross(acc,8), arcdot(acd,9), square2(sq2,10),
 diamond(dia,11), star2(st2,12), square3(sq3,13), cross2(cr2,14), star3(st3,15),
 blacksqr,(bsq,16)
```

## Fill-Area-Style
tipインタプリタで定義されているフィルエリアの名前は`opt fill`または略して`opt f`と打つことで知ることができます。  

```
tip> opt fill
names of the fill area style:
 null(-1), solid(s,0), hor(1), ver(2), p45(3), n45(4), p30(5), n30(6), hv(7), pn45(8)
```
