# Install

## (1) Install PLPLOT, GNU-readline

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

## (2) configure and make tip executable

access to https://github.com/shu-htk/tip-dev

from the "Code" button, choose "Download zip"

copy downloaded zip file (tip-dev-main.zip) to your working directry

extract zip file
```
unzip tip-dev-main.zip
```

then do
```
$ cd tip-dev-main
$ ./configure
$ make
```
the executable is comipled and output to `./bin/tip`

to copy the executable file to `$HOME/bin`
```
$ make install
```
