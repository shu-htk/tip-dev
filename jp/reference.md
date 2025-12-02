# コマンドリファレンス

## (1) tipインタープリタの起動オプション

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

## (2) tipインタープリタの構文規則

### 1行の中に複数のコマンドを記述

セミコロン`;`で分離することで複数のコマンドを実行できます

```
tip> title "x vs y1 and y2"; plot x y1; plot x y2 (rp:1) 
```

### 行をコメントアウトする

`#` を行頭に置くとその行はコメントアウトされます

```
tip> # comment out this line
```

行の途中でコメントアウトするには、`;` で分離して`#`を置きます

```
tip> plot x y ;# plotting data x and y  
```

### 変数

- **データ変数**

データ変数は数値（または文字列）の配列で、[set](ref/set.md)
コマンドによって定義されます

```
tip> set n={1,2,3}
tip> set x=sin(n)
```

上の例をC言語風に書くと以下のようなことをやっています

```
double n[]={1,2,3};
double x[sizeof(n)]; for(int i=0; i<sizeof(n); i++) x[i]=sin(n[i]);
```

データ変数の情報は [ls](ref/ls.md)コマンドで、各要素の値は
[cat](ref/cat.md)コマンドで表示されます

```
tip> ls *
n : data(num) : size=3
x : data(num) : size=3
tip> cat *
n : data(num) :  1 2 3
x : data(num) :  0.84147098481 0.90929742683 0.14112000806
```

- **マクロ変数**

マクロ変数は数値（または文字列）のスカラー値で、
[@](ref/var.md)コマンドによって定義されます  
マクロ変数はブラケット`[ ]`で囲むことで、その値が
フォーマットされた文字列に置換されます  
[ls](ref/ls.md)コマンドで情報と値の両方が表示されます

```
tip> @ n=1
tip> @ x=sin([n])  ;# this is parsed as "@ x=sin(1)"
tip> ls *
n : number [1]
x : number [0.84147098481]
```

マクロ変数はコマンドが解釈される前に文字列に置換されるので、
以下のようなことができます

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
- **環境変数**

シェルの環境変数は、`${ }`で参照することができます

```
tip> prn ${SHELL}
/bin/bash
```

## (3) MacroToolのコマンド
- [@](ref/var.md) : マクロ変数の定義と値の代入
- [args](ref/args.md) : マクロファイルの引数のデフォルト値を設定
- [++,--](ref/incr.md) : 数値型マクロ変数のインクリメント(+1), デクリメント(-1)
- [for,do,while,end](ref/loop.md) : for, do, while ループ
- [if,elif,else,fi](ref/if_fi.md) : 条件分岐
- [print](ref/print.md) : 引数をコンソールに表示
- [fmt](ref/fmt.md) : マクロ変数のフォーマットを設定
- [wait](ref/wait.md) : 指定時間（秒）又はコンソール入力を待つ
- [sys](ref/sys.md) : システムコマンドの実行
- [split](ref/split.md) : 文字列型マクロ変数を指定したデリミタで分離
- [calc](ref/calc.md) : 数値式を評価し結果を出力
- [logic](ref/logic.md) : 論理式を評価し結果を出力
- q : tipインタープリタを終了する

## (4) データの描画及び操作のコマンド
- [arc](ref/arc.md) : 円の描画
- [box](ref/box.md) : 矩形の2次元座標を描画
- [box3](ref/box3.md) : 3次元座標を描画
- [cat](ref/cat.md) : データの値を表示/連結
- [cut](ref/cut.md) : データを指定した条件でカット
- [div](ref/div.md) : 描画領域の分割
- [elem](ref/elem.md) : データ変数のある要素の値をマクロ変数に代入
- [exe](ref/exe.md) : マクロファイルの実行
- [fbox](ref/fbox.md) : 矩形エリアを塗りつぶす
- [ffit](ref/ffit.md) : 周波数領域のグラフ曲線を指定した関数でフィット
- [fit](ref/fit.md) : 2次元のデータ曲線を指定した関数でフィット
- [fit3](ref/fit3.md) : 3次元のデータ曲線を指定した関数でフィット
- [fill](ref/fill.md) : 2次元データの領域を塗りつぶす
- [font](ref/font.md) : テキストのフォントを指定
- [fplot](ref/fplot.md) : データを周波数領域でプロット（FFTパワースペクトラム）
- [help](ref/help.md) : 全コマンドリストを表示する
- [hfit](ref/hfit.md) : 1次元ヒストグラムを指定した関数でフィット
- [hplot](ref/hplot.md) : データの1次元ヒストグラムをプロット
- [hplot2](ref/hplot2.md): 2つのデータの2次元ヒストグラムをプロット
- [line](ref/line.md) : 指定した区間の線を2次元座標に描画
- [ls](ref/ls.md) : データ変数、マクロ変数の情報を表示
- [mplot](ref/mplot.md) : メッシュ（2次元の格子上の値）データを3次元でプロット
- [mread](ref/mread.md) : メッシュデータをファイルから読み込む
- [mset](ref/mset.md) : メッシュデータを定義して値を設定する
- [mwrite](ref/mwrite.md): メッシュデータをファイルに書き込む
- [opt](ref/opt.md) : グローバルオプションの値の表示、設定
- [plot](ref/plot.md) : 2つのデータを2次元でプロット
- [plot3](ref/plot3.md) : 3つのデータを3次元でプロット
- [read](ref/read.md) : データをファイルから読み込む
- [rm](ref/rm.md) : データ変数、マクロ変数をメモリから削除
- [set](ref/set.md) : データ変数の定義と値の代入
- [sort](ref/sort.md) : 指定したデータでインデックスソート（昇順）
- [stat](ref/stat.md) : データの統計情報を表示
- [symb](ref/symb.md) : 指定した2次元座標にシンボルマークを描画
- [text](ref/text.md) : 指定した2次元座標にテキストを描画
- [title](ref/title.md) : グラフのフレーム上部にタイトルを描画
- [tfmt](ref/tfmt.md) : x軸を指定したフォーマットで時刻表示にする
- [vp](ref/vp.md) : ウィンドウに対する描画領域を指定する
- [write](ref/write.md) : データをファイルに書き込む
- [xerr](ref/xerr.md) : x方向の誤差棒をプロットする
- [xlab](ref/xlab.md) : x軸のラベルを指定する
- [yerr](ref/yerr.md) : y方向の誤差棒をプロットする
- [ylab](ref/ylab.md) : y軸のラベルを指定する
- [zlab](ref/zlab.md) : z軸のラベルを指定する

## (5) EPICS CA のコマンド(オプション機能)

- [cainfo](ref/cainfo.md) : EPICSレコードの情報を表示
- [caget](ref/caget.md) : EPICSレコードの値を取得し表示、又は変数に代入
- [caput](ref/caput.md) : EPICSレコードに値を式、又は変数から代入
- [camon](ref/camon.md) : EPICSレコードに常時接続しモニタする
- [cacheck](ref/cacheck.md): モニタしているEPICSレコードが更新したかチェック
- [caclose](ref/caclose.md): モニタしているEPICSレコードの常時接続を閉じる
