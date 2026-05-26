##  tipインタープリタの構文規則


### コマンドは行単位で実行される

```
tip> title "x vs y1 and y2"
tip> plot x y1
tip> plot x y2 (rp:1) 
```

### １行の中に複数のコマンドを記述

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
