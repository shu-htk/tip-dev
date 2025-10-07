# Install

(1) install plplot, readline

- Ubuntu 24.04

```
sudo apt update
sudo apt upgrade
sudo apt install g++
sudo apt install libplplot-dev
sudo apt install plplot-driver-cairo
```
- AlmaLinax 9

```
sudo dnf update
sudo dnf upgrade
# sudo dnf install dnf-plugins-core     (<-- this may not neccessary)
# sudo dnf config-manager --enable crb  (<-- this may not neccessary)
sudo dnf install epel-release
sudo dnf install epel-next-release
sudo dnf install g++
sudo dnf install plplot-devel
sudo dnf install readline-devel
```

(2) configure, make tip executable file

access https://github.com/shu-htk/tip-dev

-- "Code" Tab -> "Code" button ->  "Download zip"

extract zip file

if there is not $HOME/bin
```
$ mkdir ~/bin
```
```
$ cd tip-dev
$ ./configure
$ make
```
the executable is comipled to ./bin/tip

to copy the executable file to $HOME/bin

```
$ make install
```






