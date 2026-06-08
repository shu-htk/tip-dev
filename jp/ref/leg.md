# legend
```
tip> legend
Usage: legend [command] [(opt)]
Draw legend on the existing graph. (alias: leg)
command:
 show [xpos,ypos]
   xpos: right(r), middle(m), left(l) : (default is right)
   ypos: top(t), middle(m), bottom(b) : (default is top)
 add [string]
   add legend string.
 ls
   list legend strings.
 rm
   remove legend strings.
Example:
   plot x y (st:plus lg:*)
   legent show l,m
It draws plus marker '+' and text 'x : y' at left,middle of the grapgh
```

> v1.2.1 以降に使える機能

凡例(legend)を設定、表示する

例
```
tip> box 0 1 0 1         ;# グラフの枠を表示
tip> legend add "Hello"  ;# 凡例を追加（1段目）
tip> legend add "World"  ;# 凡例を追加（2段目）
tip> legend show         ;# 凡例を表示（デフォルト位置：右上）
```


## `lg:`オプション

以下のコマンド：

`plot`, `fit`,`hplot`,`hfit`,`fplot`,`ffit`

では、`lg:`オプションで指定した文字列がそのグラフの線種、シンボルと共に
凡例に追加される

なお、凡例の文字列が`*`であった場合、以下の文字列に変換される

|コマンド例|変換後の文字列|
|---|---|
|`plot x y (lg:*)`|`x : y`（xの変数名 : yの変数名）|
|`fit x y lin (lg:*)`|`lin fit` (関数名 + fit) |
|`hfit x gaus (lg:*)`|`gaus fit` (関数名 + fit) |
|`fplot x y (lg:*)`|`y : FFT` (yの変数名 + FFT)|


例
```
tip> set x = range(10,1,10)
tip> set y = x
tip> plot x y (lw:0 st:plus sc:red lg:*) ;# デフォルトの凡例（シンボルと変数名）
tip> legend show left,top                ;# 凡例を表示（指定位置：左上）
```

## `lg:`オプション内で使える特別なタグ

|タグ名|表示される情報|使用例|
|---|---|---|
|`%stat`|統計情報|`hplot x (lg:*%stat)`|
|`%fit`|フィッティング係数|`fit x y lin (lg:*%fit)`|
|`%win`|窓関数名|`fplot v (lg:*%win)`|

マクロの例：
[ex28](../../doc/ex/ex28.md),
[ex29](../../doc/ex/ex29.md),
[ex30](../../doc/ex/ex30.md)


