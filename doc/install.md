# Install

## Install PLPLOT, GNU-readline

- Ubuntu 24.04
```
sudo apt update
sudo apt upgrade
sudo apt install g++
sudo apt install libplplot-dev
sudo apt install plplot-driver-cairo
sudo apt install libreadline-dev
```
- AlmaLinax 9
```
sudo dnf update
sudo dnf upgrade
# sudo dnf install dnf-plugins-core     (<-- this may not be neccessary)
# sudo dnf config-manager --enable crb  (<-- this may not be neccessary)
sudo dnf install epel-release
sudo dnf install epel-next-release
sudo dnf install g++
sudo dnf install plplot-devel
sudo dnf install readline-devel
```

## configure, make tip executable

access to https://github.com/shu-htk/tip-dev

> "Code" Tab -> "Code" button ->  "Download zip"

extract downloaded zip file

if there is not $HOME/bin
```
$ mkdir ~/bin
```
then do,
```
$ cd tip-dev
$ ./configure
$ make
```
the executable is comipled and output to ./bin/tip

to copy the executable file to $HOME/bin

```
$ make install
```







