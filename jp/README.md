# tip - tiny interactive plot

Tipはコマンドラインベースのデータプロットツールです。
C++で記述されており
[PLPLOT](https://plplot.sourceforge.net/)
と
[GNU readline](https://cgit.git.savannah.gnu.org/cgit/readline.git)
に依存しています。
基本的にLinuxやその他のUnix系OSで動作します。
既存のプロットツールに比べて機能は少ないですが、汎用性よりも使いやすさを重視しています。

## 特徴

- 2Dおよび3Dで曲線をプロットする
- 2Dおよび3Dでヒストグラムをプロットする
- FFTパワースペクトルをプロットする
- 曲線とヒストグラムへのデータフィッティング
- データのソート、切り取り
- 制御 (`for`,`do`,`while`,`end`,`if`,`elif`,`else`,`fi`)
- マクロファイルを実行する
- PDFまたはPNGファイルに保存する
- [EPICS](https://epics-controls.org/) CAアクセス（オプション）

## インストール

- [how to install](install.md)

## チュートリアル

- [tutorial](tutorial.md)

## マクロファイルの例

- [macro examples](examples.md)

## コマンドリファレンス

- [command reference](reference.md)

***
*[English document](../README.md)*
