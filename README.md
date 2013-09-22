HighGUI3DCG
===========

C++による簡単実習 3次元CG入門　第2版 のサンプルコードを
Macで動作させるために， ウィンドウ周りの処理をやっつけ実装しました．
未実装機能や不具合が多々ありますが， EX1〜EX8までは一応動作を確認できたので公開します．

#使い方
## OpenCVの導入
バックエンドにHighGUIを利用しているため，OpenCVの導入が不可欠です．
自身の環境に合わせてHomeBrewやMacPortsなどから導入してください．

## サンプルコードのDL・展開
[ここ](http://www.morikita.co.jp/exclusive/download/738)からサンプルコードをダウンロードし，展開します．
```bash
$ ls
084142src.zip
$ unzip 084142src.zip
$ tar -zxvf cg_gcc.tar.gz
```

## リポジトリのチェックアウトとマージ
```bash
$ git clone https://github.com/ar90n/HighGUI3DCG.git
Cloning into 'HighGUI3DCG'...
remote: Counting objects: 15, done.
remote: Compressing objects: 100% (11/11), done.
remote: Total 15 (delta 1), reused 10 (delta 0)
Unpacking objects: 100% (15/15), done.
$ cp -R HighGUI3DCG/* cg_gcc/
```

## ライブラリのビルド
```bash
$ cd cg_gcc
$ scons
scons: Reading SConscript files ...
scons: done reading SConscript files.
scons: Building targets ...
g++ -o src/win.o -c -I/usr/local/Cellar/opencv/2.4.5/include/opencv -I/usr/local/Cellar/opencv/2.4.5/include -Iinc src/win.cpp
g++ -o src/win_highgui.o -c -I/usr/local/Cellar/opencv/2.4.5/include/opencv -I/usr/local/Cellar/opencv/2.4.5/include -Iinc src/win_highgui.cpp
ar rc src/win.a src/win.o src/win_highgui.o
ranlib src/win.a
scons: done building targets.
```

## Makefileの修正
```bash
$ cd prj
$ patch -u < Makefile.patch 
patching file Makefile
```

## サンプルのビルド
```bash
$ cd ../src/
$ make -f ../prj/Makefile EX4_1
g++ -g -w -O3 -fno-for-scope  -fthis-is-variable -I ../inc `pkg-config --cflags opencv` -c ../src/EX4_1.cpp
g++ -g -w -O3 -fno-for-scope  -fthis-is-variable -I ../inc `pkg-config --cflags opencv` -c ../src/point.cpp
g++ -g -w -O3 -fno-for-scope  -fthis-is-variable -I ../inc `pkg-config --cflags opencv` -c ../src/line.cpp
g++ -g -w -O3 -fno-for-scope  -fthis-is-variable -I ../inc `pkg-config --cflags opencv` -c ../src/tmatrix.cpp
g++ -g -w -O3 -fno-for-scope  -fthis-is-variable -I ../inc `pkg-config --cflags opencv` -c ../src/ray.cpp
g++ -g -w -O3 -fno-for-scope  -fthis-is-variable -I ../inc `pkg-config --cflags opencv` -c ../src/polygon.cpp
g++ -g -w -O3 -fno-for-scope  -fthis-is-variable -I ../inc `pkg-config --cflags opencv` -c ../src/surface.cpp
g++ -g -w -O3 -fno-for-scope  -fthis-is-variable -I ../inc `pkg-config --cflags opencv` -c ../src/etc.cpp
g++ -g -w -O3 -fno-for-scope  -fthis-is-variable -I ../inc `pkg-config --libs opencv` -lm  EX4_1.o point.o line.o tmatrix.o ray.o polygon.o surface.o etc.o ../src/win.a -o EX4_1
```
