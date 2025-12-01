# インストール

現在、以下のシステムで動作確認しています。

- Ubuntu 24.04
- AlmaLinux 9.5
- macOS 12.7.6 (MacBook Air 2015 MJVM2J/A)

基本的にPLPLOT と GNU readline がインストールされていれば インストールできると思います。

## (1) PLPLOT, GNU-readlineライブラリのインストール

以下のようにパッケージマネージャーを用いてインストールしてください。

- **Ubuntu 24.04**
```
sudo apt update
sudo apt upgrade
sudo apt install g++
sudo apt install libplplot-dev
sudo apt install plplot-driver-cairo
sudo apt install libreadline-dev
```
- **AlmaLinux 9**
```
sudo dnf update
sudo dnf upgrade
sudo dnf install dnf-plugins-core     (<-- this may not be necessary)
sudo dnf config-manager --enable crb
sudo dnf install epel-release
sudo dnf install epel-next-release
sudo dnf install g++
sudo dnf install plplot-devel
sudo dnf install readline-devel
```
- **Windows 11**

WSL2上に各種Linuxディストリビューションを動作させ、
その上でパッケージマネージャーを用いてインストールしてください。

WSLについては以下のリンクを参考にしてください。

[https://learn.microsoft.com/windows/wsl/install](https://learn.microsoft.com/windows/wsl/install)

ちなみにCygwinにもインストールできます。
必要なパッケージは「PLPLOT cygwin」等のキーワードでネット検索してみてください。
（例） [https://sourceforge.net/p/plplot/wiki/Setup_cygwin/](https://sourceforge.net/p/plplot/wiki/Setup_cygwin/)

- **macOS 12.7.6**
1. MacPortsのインストール
 [https://www.macports.org](https://www.macports.org)
2. XQuartz のインストール
 [https://www.xquartz.org](https://www.xquartz.org)
3. 端末から PLPLOT, readline のインストール  
```
 $ sudo port install plplot
 $ sudo port install readline
```

## (2) tip の実行ファイルのコンパイル方法


GitHubのリポジトリ： 
[https://github.com/shu-htk/tip-dev](https://github.com/shu-htk/tip-dev)

“Code” プルダウンメニューから “Download zip” 
を選んでアーカイブファイルをダウンロードします。

直接以下のURLからダウンロードすることもできます。
[https://github.com/shu-htk/tip-dev/archive/refs/heads/main.zip](https://github.com/shu-htk/tip-dev/archive/refs/heads/main.zip)

ダウンロードしたファイルをご自分のワーク用ディレクトリにコピーしてください。

コンソール端末を開いて以下のコマンドでzipファイルを解凍します

```
unzip tip-dev-main.zip
```

その後、以下のようにして、configureスクリプトを実行し、
makeコマンドを 使ってコンパイルします。

```
cd tip-dev-main
./configure
make
```

コンパイルされた実行ファイルはカレントディレクトリ上の `./bin/tip` に出力されます。

シェルに$HOME/binへのコマンドパスがある場合は、

```
make install
```

とすると実行ファイルが `$HOME/bin` にコピーされます。


## (3) my_macro について


`tip` をインストールすると、実行ファイル `my_macro` もインストールされます。
これはソースファイルに同梱されているヘッダーオンリーのクラスライブラリ
[MacroTool](ref/MacroTool.md)
を使った簡単なインタープリタコマンドです

## (4) EPICS CA の有効化 (オプション機能)

お使いのコンピュータにEPICSが既にインストールされている場合は、
環境変数 EPICS_BASE が設定されているかどうかを確認してください。
設定されている場合、Tipのconfigureスクリプトを実行した際に、
EPICS CAを有効化したMakefileが作成されます。

EPICSがインストールされていない場合は以下の手順でEPICS環境を構築し設定する必要があります。

EPICSソースのアーカイブを以下のURLからダウンロードしてください。


- stable:: 
[https://epics-controls.org/download/base/base-3.15.9.tar.gz](https://epics-controls.org/download/base/base-3.15.9.tar.gz)
- new:
[https://epics-controls.org/download/base/base-7.0.9.tar.gz](https://epics-controls.org/download/base/base-7.0.9.tar.gz)

たとえば、新しいバージョンを$HOME/epicsにインストールするなら、

```
mkdir -p $HOME/epics
cp base-7.0.9.tar.gz $HOME/epics
cd $HOME/epics
tar zxf base-7.0.9.tar.gz
cd base-7.0.9
make
```

としてください。コンパイルが完了するまで少し時間がかかります。

その後、環境変数を以下のように設定してください。

```
export EPICS_BASE=$HOME/epics/base-7.0.9
```
